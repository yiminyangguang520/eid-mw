/* ****************************************************************************

 * eID Middleware Project.
 * Copyright (C) 2008-2009 FedICT.
 *
 * This is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License version
 * 3.0 as published by the Free Software Foundation.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this software; if not, see
 * http://www.gnu.org/licenses/.

**************************************************************************** */

#include "CapiSign.h"

std::wstring CCapiSign::_ToUnicode(const string& utf8string) {

	if (utf8string.length() == 0) 
		return wstring();

	UINT wStringLength = MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), (int)utf8string.length() , NULL, 0);
	if (wStringLength == 0) 
		return std::wstring();

	LPWSTR pws = new WCHAR[wStringLength];
	if ((wStringLength = MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), (int)utf8string.length(), pws, wStringLength)) == 0)   {
		delete[] pws;
		return std::wstring();
	}
	std::wstring result(pws, pws + wStringLength);
	delete[] pws;
	return result;
}



string CCapiSign::SignMessage(const Buffer& cert, const string& msg) {


	HCERTSTORE hstore = NULL;

	HCRYPTPROV hprov = NULL;

	if (! CryptAcquireContextW(&hprov, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
		string err = "SignMessage: CryptAcquireContext [VerifyContext]";
		throw CErrorFmt::FormatError(::GetLastError(), err.c_str()); 
	}


	hstore = CertOpenSystemStoreW(0, L"MY");
	if (hstore == NULL) {
		CryptReleaseContext(hprov, 0);
		string err = "SignMessage: CertOpenSystemStore";
		throw CErrorFmt::FormatError(::GetLastError(), err.c_str()); 
	}

	PCCERT_CONTEXT findcontext = CertCreateCertificateContext(
		X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
		(const BYTE *)&cert[0], 
		(DWORD)cert.size());

	if (findcontext == NULL) {
		CryptReleaseContext(hprov, 0);
		CertCloseStore(hstore, 0);
		string err = "SignMessage: CertCreateCertificateContext";
		throw CErrorFmt::FormatError(::GetLastError(), err.c_str()); 
	}
	DWORD dwsize = 0;

	dwsize = CertGetNameStringW(findcontext, CERT_NAME_ATTR_TYPE, 0, szOID_COMMON_NAME, NULL, dwsize);

	auto_vec<WCHAR> pname(new WCHAR[dwsize]);
	dwsize = CertGetNameStringW(findcontext, CERT_NAME_ATTR_TYPE, 0, szOID_COMMON_NAME, pname.get(), dwsize);
	std::wstring wname = pname.get();

	DWORD dwlen;
	if (! CryptHashCertificate(hprov, CALG_SHA1, 0, findcontext->pbCertEncoded, findcontext->cbCertEncoded, NULL, &dwlen)) {
		CertFreeCertificateContext(findcontext);
		CryptReleaseContext(hprov, 0);
		CertCloseStore(hstore, 0);
		string err = "SignMessage: CryptHashCertificate";
		throw CErrorFmt::FormatError(::GetLastError(), err.c_str()); 
	}

	auto_vec<BYTE> certhash(new BYTE[dwlen]);
	if (! CryptHashCertificate(hprov, CALG_SHA1, 0, findcontext->pbCertEncoded, findcontext->cbCertEncoded, certhash.get(), &dwlen)) {
		CertFreeCertificateContext(findcontext);
		CryptReleaseContext(hprov, 0);
		CertCloseStore(hstore, 0);
		string err = "SignMessage: CryptHashCertificate";
		throw CErrorFmt::FormatError(::GetLastError(), err.c_str()); 
	}
	string encodedhash = base64_encode(certhash.get(), dwlen);

	PCCERT_CONTEXT context = CertFindCertificateInStore(
		hstore, 
		X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, 
		CERT_FIND_ANY,
		0,
		NULL,
		NULL);
	while (context != NULL) {
		dwsize = CertGetNameStringW(context, CERT_NAME_ATTR_TYPE, 0, szOID_COMMON_NAME, NULL, dwsize);
		auto_vec<WCHAR> pfname(new WCHAR[dwsize]);
		dwsize = CertGetNameStringW(context, CERT_NAME_ATTR_TYPE, 0, szOID_COMMON_NAME, pfname.get(), dwsize);
		std::wstring wfname = pfname.get();

		if (! CryptHashCertificate(hprov, CALG_SHA1, 0, context->pbCertEncoded, context->cbCertEncoded, NULL, &dwlen)) {
			CertFreeCertificateContext(context);
			CryptReleaseContext(hprov, 0);
			CertCloseStore(hstore, 0);
			string err = "SignMessage: CryptHashCertificate";
			throw CErrorFmt::FormatError(::GetLastError(), err.c_str()); 
		}
		auto_vec<BYTE> fcerthash(new BYTE[dwlen]);
		if (! CryptHashCertificate(hprov, CALG_SHA1, 0, context->pbCertEncoded, context->cbCertEncoded, fcerthash.get(), &dwlen)) {
			CertFreeCertificateContext(context);
			CryptReleaseContext(hprov, 0);
			CertCloseStore(hstore, 0);
			string err = "SignMessage: CryptHashCertificate";
			throw CErrorFmt::FormatError(::GetLastError(), err.c_str()); 
		}
		string fencodedhash = base64_encode(fcerthash.get(), dwlen);

		if ((wname.size() == wfname.size()) && (wname == wfname) && (encodedhash == fencodedhash)) {
			break;
		}
		context = CertFindCertificateInStore(
			hstore, 
			X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, 
			CERT_FIND_ANY,
			0,
			NULL,
			context);

	}
	CertFreeCertificateContext(findcontext);

	if (context == NULL) {
		CryptReleaseContext(hprov, 0);
		CertCloseStore(hstore, 0);
		std::string err = "SignMessage: AUTH certificate not found.";
		throw CErrorFmt::FormatError(::GetLastError(), err.c_str()); 
	}

	std::wstring csp = L"";
	std::wstring container = L"";

	DWORD dwPropId = CertEnumCertificateContextProperties(context, 0);
	while (dwPropId != 0) {
		if (CERT_KEY_PROV_INFO_PROP_ID == dwPropId) {
			DWORD cbData = 0;
			PCRYPT_KEY_PROV_INFO pProvInfo = NULL;
			if (CertGetCertificateContextProperty(context, dwPropId, NULL, &cbData)) {
				auto_vec<BYTE> prov_data(new BYTE[cbData]);
				PCRYPT_KEY_PROV_INFO pProvInfo = (PCRYPT_KEY_PROV_INFO)prov_data.get();
				if (CertGetCertificateContextProperty(context, dwPropId, pProvInfo, &cbData)) {
					csp = pProvInfo->pwszProvName;
					container = pProvInfo->pwszContainerName;
					break;
				}
			}
		}
		dwPropId = CertEnumCertificateContextProperties(context, dwPropId);
	}


	if (hstore != NULL)
		CertCloseStore(hstore, 0);

	CryptReleaseContext(hprov, 0);

	//**** debug ***
	// wcout << L"Container: " << container << L",CSP: " << csp << wstring(L"\r\n");
	//**** debug ***

	if (! CryptAcquireContextW(&hprov, container.c_str(), csp.c_str(), PROV_RSA_FULL, 0)) {
		string err = "SignMessage: CryptAcquireContext [OpenKeySet]";
		throw CErrorFmt::FormatError(::GetLastError(), err.c_str()); 
	}


	HCRYPTHASH hhash;

	if (! CryptCreateHash(hprov, CALG_SHA1, 0, 0, &hhash)) {
        DWORD le = ::GetLastError();
		CertFreeCertificateContext(context);
		CryptReleaseContext(hprov, 0);
		string err = "SignMessage: CryptCreateHash";
		throw CErrorFmt::FormatError(le, err.c_str()); 
	}


	if (! CryptHashData(hhash, (BYTE *)msg.c_str(), (DWORD)msg.size(), 0)) {
        DWORD le = ::GetLastError();
		CertFreeCertificateContext(context);
		CryptReleaseContext(hprov, 0);
		CryptDestroyHash(hhash);
		string err = "SignMessage: CryptHashData";
		throw CErrorFmt::FormatError(le, err.c_str()); 
	}

	DWORD dwhashlen;
	if (! CryptGetHashParam(hhash, HP_HASHVAL, NULL, &dwhashlen, 0))  {
        DWORD le = ::GetLastError();
		CertFreeCertificateContext(context);
		CryptReleaseContext(hprov, 0);
		CryptDestroyHash(hhash);
		string err = "SignMessage: CryptGetHashParam";
		throw CErrorFmt::FormatError(le, err.c_str()); 
	}
	auto_vec<BYTE> hashvalue(new BYTE[dwhashlen]);
	if (! CryptGetHashParam(hhash, HP_HASHVAL, hashvalue.get(), &dwhashlen, 0))  {
        DWORD le = ::GetLastError();
		CertFreeCertificateContext(context);
		CryptReleaseContext(hprov, 0);
		CryptDestroyHash(hhash);
		string err = "SignMessage: CryptGetHashParam";
		throw CErrorFmt::FormatError(le, err.c_str()); 
	}

	DWORD dwsiglen;
	if (! CryptSignHash(hhash, AT_SIGNATURE, NULL, 0, NULL, &dwsiglen)) {
        DWORD le = ::GetLastError();
		CertFreeCertificateContext(context);
		CryptReleaseContext(hprov, 0);
		CryptDestroyHash(hhash);
		string err = "SignMessage: CryptSignHash";
		throw CErrorFmt::FormatError(le, err.c_str()); 
	}
	auto_vec<BYTE> signature(new BYTE[dwsiglen]);
	if (! CryptSignHash(hhash, AT_SIGNATURE, NULL, 0, signature.get(), &dwsiglen)) {
        DWORD le = ::GetLastError();
		CertFreeCertificateContext(context);
		CryptReleaseContext(hprov, 0);
		CryptDestroyHash(hhash);
		string err = "SignMessage: CryptSignHash";
		throw CErrorFmt::FormatError(le, err.c_str()); 
	}


	// CAPI produces reversed signatures
	auto_vec<BYTE> proper_signature(new BYTE[dwsiglen]);
	BYTE* p1 = signature.get() + dwsiglen;
	BYTE *p2 = proper_signature.get();
	for (DWORD i = 0; i < dwsiglen; ++i)
		*p2++ = *--p1;


	string Result = base64_encode(proper_signature.get(), dwsiglen);

	if (NULL != context)
		CertFreeCertificateContext(context);

	if (NULL != hhash)
		CryptDestroyHash(hhash);

	if (NULL != hprov)
		CryptReleaseContext(hprov, 0);


	return Result;

}

bool CCapiSign::_StoreUserCerts(PCCERT_CONTEXT pCertContext, unsigned char KeyUsageBits,  const std::wstring& containerserial) {

	// build keycontainer name
	std::wstring strContainerName;
	if (KeyUsageBits & CERT_NON_REPUDIATION_KEY_USAGE) {
		strContainerName = L"Signature(";
	} else {
		strContainerName = L"Authentication(";
	}
	strContainerName += containerserial;
	strContainerName += L")";

	// add to store if not already present
	PCCERT_CONTEXT  pDesiredCert	= NULL;
	HCERTSTORE		hMyStore		= CertOpenSystemStoreW(NULL, L"MY");
	if ( NULL != hMyStore )	{
		// ----------------------------------------------------
		// look if we already have the certificate in the store
		// If the certificate is not found --> NULL
		// ----------------------------------------------------
		if( NULL != (pDesiredCert = CertFindCertificateInStore(hMyStore, X509_ASN_ENCODING, 0, CERT_FIND_EXISTING, pCertContext , NULL))) {
			// ----------------------------------------------------
			// certificate is already in the store, then just return
			// ----------------------------------------------------
			CertCloseStore (hMyStore, CERT_CLOSE_STORE_FORCE_FLAG);
			return true;
		}
		CRYPT_KEY_PROV_INFO CryptKeyProvInfo;
		CRYPT_KEY_PROV_INFO* pCryptKeyProvInfo  = &CryptKeyProvInfo;
		pCryptKeyProvInfo->pwszContainerName	= (LPWSTR)strContainerName.c_str();
		pCryptKeyProvInfo->pwszProvName			= L"Belgium Identity Card CSP";
		pCryptKeyProvInfo->dwProvType			= PROV_RSA_FULL;
		pCryptKeyProvInfo->dwFlags				= 0;
		pCryptKeyProvInfo->cProvParam			= 0;
		pCryptKeyProvInfo->rgProvParam			= NULL;
		pCryptKeyProvInfo->dwKeySpec			= AT_KEYEXCHANGE;

		// Set the property.
		if (CertSetCertificateContextProperty(pCertContext, CERT_KEY_PROV_INFO_PROP_ID, CERT_STORE_NO_CRYPT_RELEASE_FLAG, pCryptKeyProvInfo)) {
			// Set friendly names for the certificates
			unsigned long	ulID = 0;
			if (KeyUsageBits & CERT_NON_REPUDIATION_KEY_USAGE) {
				ulID = 0x03;
			} else {
				ulID = 0x02;
			}

			DWORD dwsize = 0;
			dwsize = CertGetNameStringW(pCertContext, CERT_NAME_ATTR_TYPE, 0, szOID_COMMON_NAME, NULL, dwsize);
			auto_vec<WCHAR> pname(new WCHAR[dwsize]);
			dwsize = CertGetNameStringW(pCertContext, CERT_NAME_ATTR_TYPE, 0, szOID_COMMON_NAME, pname.get(), dwsize);
			CRYPT_DATA_BLOB tpFriendlyName = {0, 0};
			tpFriendlyName.pbData = (BYTE *)pname.get();
			tpFriendlyName.cbData = dwsize * sizeof(WCHAR);

			if (CertSetCertificateContextProperty(pCertContext, CERT_FRIENDLY_NAME_PROP_ID, CERT_STORE_NO_CRYPT_RELEASE_FLAG, &tpFriendlyName)) {
				if (KeyUsageBits & CERT_NON_REPUDIATION_KEY_USAGE) {
					CertAddEnhancedKeyUsageIdentifier (pCertContext, szOID_PKIX_KP_EMAIL_PROTECTION);
				} else {
					CertAddEnhancedKeyUsageIdentifier (pCertContext, szOID_PKIX_KP_EMAIL_PROTECTION);
					CertAddEnhancedKeyUsageIdentifier (pCertContext, szOID_PKIX_KP_CLIENT_AUTH);
				}
				CertAddCertificateContextToStore(hMyStore, pCertContext, CERT_STORE_ADD_REPLACE_EXISTING, NULL);
                CertFreeCertificateContext(pCertContext);
				CertCloseStore (hMyStore, CERT_CLOSE_STORE_FORCE_FLAG);
                return true;
			}
		}
	}
	CertCloseStore(hMyStore, CERT_CLOSE_STORE_FORCE_FLAG);
	return false;
}

bool CCapiSign::ImportCert(const Buffer &cert,  const Buffer& tokenInfo) {

	std::string hexserial;
	hexserial.reserve(33);
	// serial = 16 bytes starting from tokeninfo[7] 
	for (int i = 7; i < 7 + 16; ++i) {
		char buf[4];
		sprintf_s(buf, sizeof(buf), "%2.2X", tokenInfo.at(i));
		hexserial.append(buf);
	}
	std::wstring containerserial = _ToUnicode(hexserial);
	PCCERT_CONTEXT	pCertContext = NULL;

	pCertContext = CertCreateCertificateContext(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, (const BYTE *)&cert[0], (DWORD)cert.size());
	if (pCertContext) {
		unsigned char KeyUsageBits = 0; // Intended key usage bits copied to here.
		CertGetIntendedKeyUsage(X509_ASN_ENCODING, pCertContext->pCertInfo, &KeyUsageBits, 1);
		bool Result = CCapiSign::_StoreUserCerts(pCertContext, KeyUsageBits, containerserial);
		return Result;
	} else
		return false;
}

