/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.35
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

namespace be.belgium.eid {

using System;
using System.Runtime.InteropServices;

/// <summary>Class that represent one certificate.</summary>
public class BEID_Certificate : BEID_Crypto {
  private HandleRef swigCPtr;

  internal BEID_Certificate(IntPtr cPtr, bool cMemoryOwn) : base(beidlib_dotNetPINVOKE.BEID_CertificateUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(BEID_Certificate obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~BEID_Certificate() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if(swigCPtr.Handle != IntPtr.Zero && swigCMemOwn) {
        swigCMemOwn = false;
        beidlib_dotNetPINVOKE.delete_BEID_Certificate(swigCPtr);
      }
      swigCPtr = new HandleRef(null, IntPtr.Zero);
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  /// <summary>Return the label of the certificate.</summary>
  public string getLabel()
  {
    string ret = beidlib_dotNetPINVOKE.BEID_Certificate_getLabel(swigCPtr);
    if (beidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw beidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  /// <summary>Return the id of the certificate.</summary>
  public uint getID()
  {
    uint ret = beidlib_dotNetPINVOKE.BEID_Certificate_getID(swigCPtr);
    if (beidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw beidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  /// <summary>Return the status of the certificate using default validation level (from config).</summary>
  public BEID_CertifStatus getStatus()
  {
    BEID_CertifStatus ret = (BEID_CertifStatus)beidlib_dotNetPINVOKE.BEID_Certificate_getStatus__SWIG_0(swigCPtr);
    if (beidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw beidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  /// <summary>Return the status of the certificate.</summary>
  public BEID_CertifStatus getStatus(BEID_ValidationLevel crl, BEID_ValidationLevel ocsp)
  {
    BEID_CertifStatus ret = (BEID_CertifStatus)beidlib_dotNetPINVOKE.BEID_Certificate_getStatus__SWIG_1(swigCPtr, (int)crl, (int)ocsp);
    if (beidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw beidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  /// <summary>Return the type of the certificate.</summary>
  public BEID_CertifType getType()
  {
    BEID_CertifType ret = (BEID_CertifType)beidlib_dotNetPINVOKE.BEID_Certificate_getType(swigCPtr);
    if (beidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw beidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  /// <summary>Return the content of the certificate.</summary>
  public BEID_ByteArray getCertData()
  {
    BEID_ByteArray ret = new BEID_ByteArray(beidlib_dotNetPINVOKE.BEID_Certificate_getCertData(swigCPtr), false);
    if (beidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw beidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  /// <summary>Return the content of the certificate without ending zero.</summary>
  public void getFormattedData(BEID_ByteArray data)
  {
    beidlib_dotNetPINVOKE.BEID_Certificate_getFormattedData(swigCPtr, BEID_ByteArray.getCPtr(data));
    if (beidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw beidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
  }

  /// <summary>Return the serial number of the certificate.</summary>
  public string getSerialNumber()
  {
    string ret = beidlib_dotNetPINVOKE.BEID_Certificate_getSerialNumber(swigCPtr);
    if (beidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw beidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  /// <summary>Return the name of the owner of the certificate.</summary>
  public string getOwnerName()
  {
    string ret = beidlib_dotNetPINVOKE.BEID_Certificate_getOwnerName(swigCPtr);
    if (beidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw beidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  /// <summary>Return the name of the issuer of the certificate.</summary>
  public string getIssuerName()
  {
    string ret = beidlib_dotNetPINVOKE.BEID_Certificate_getIssuerName(swigCPtr);
    if (beidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw beidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  /// <summary>Return the validity begin date of the certificate.</summary>
  public string getValidityBegin()
  {
    string ret = beidlib_dotNetPINVOKE.BEID_Certificate_getValidityBegin(swigCPtr);
    if (beidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw beidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  /// <summary>Return the validity end date of the certificate.</summary>
  public string getValidityEnd()
  {
    string ret = beidlib_dotNetPINVOKE.BEID_Certificate_getValidityEnd(swigCPtr);
    if (beidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw beidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  /// <summary>Return the length of public/private key on the certificate.</summary>
  public uint getKeyLength()
  {
    uint ret = beidlib_dotNetPINVOKE.BEID_Certificate_getKeyLength(swigCPtr);
    if (beidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw beidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  /// <summary>Return true if this is a root certificate.</summary>
  public bool isRoot()
  {
    bool ret = beidlib_dotNetPINVOKE.BEID_Certificate_isRoot(swigCPtr);
    if (beidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw beidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  /// <summary>Return the test status.</summary>
  /// <returns>
  /// - true if test certificate
  /// - false if good one
  /// </returns>
  public bool isTest()
  {
    bool ret = beidlib_dotNetPINVOKE.BEID_Certificate_isTest(swigCPtr);
    if (beidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw beidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  /// <summary>Return true if the certificate chain end by the one of beid root.</summary>
  public bool isFromBeidValidChain()
  {
    bool ret = beidlib_dotNetPINVOKE.BEID_Certificate_isFromBeidValidChain(swigCPtr);
    if (beidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw beidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  /// <summary>This certificate comes from the card.</summary>
  public bool isFromCard()
  {
    bool ret = beidlib_dotNetPINVOKE.BEID_Certificate_isFromCard(swigCPtr);
    if (beidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw beidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  /// <summary>
  /// Return the issuer certificate.
  /// </summary>
  /// <remarks>
  /// If there is no issuer (root), BEID_ExCertNoIssuer exception is thrown.
  /// </remarks>
  public BEID_Certificate getIssuer()
  {
    BEID_Certificate ret = new BEID_Certificate(beidlib_dotNetPINVOKE.BEID_Certificate_getIssuer(swigCPtr), false);
    if (beidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw beidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  /// <summary>Return the number of children for this certificate.</summary>
  public uint countChildren()
  {
    uint ret = beidlib_dotNetPINVOKE.BEID_Certificate_countChildren(swigCPtr);
    if (beidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw beidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  /// <summary>
  /// Return the children certificate (certificate that has been issued by this one).
  /// </summary>
  /// <remarks>
  /// Throw BEID_ExParamRange exception if the index is out of range.
  /// </remarks>
  /// <param name="ulIndex">is the children index (the index for the first child is 0</param>  )
  public BEID_Certificate getChildren(uint ulIndex)
  {
    BEID_Certificate ret = new BEID_Certificate(beidlib_dotNetPINVOKE.BEID_Certificate_getChildren(swigCPtr, ulIndex), false);
    if (beidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw beidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  /// <summary>Return the crl of the certificate.</summary>
  public BEID_Crl getCRL()
  {
    BEID_Crl ret = new BEID_Crl(beidlib_dotNetPINVOKE.BEID_Certificate_getCRL(swigCPtr), false);
    if (beidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw beidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  /// <summary>Return the ocsp response object of the certificate.</summary>
  public BEID_OcspResponse getOcspResponse()
  {
    BEID_OcspResponse ret = new BEID_OcspResponse(beidlib_dotNetPINVOKE.BEID_Certificate_getOcspResponse(swigCPtr), false);
    if (beidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw beidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  /// <summary>Verify the certificate trough CRL validation.</summary>
  public BEID_CertifStatus verifyCRL(bool forceDownload)
  {
    BEID_CertifStatus ret = (BEID_CertifStatus)beidlib_dotNetPINVOKE.BEID_Certificate_verifyCRL__SWIG_0(swigCPtr, forceDownload);
    if (beidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw beidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  /// <summary>Verify the certificate trough CRL validation.</summary>
  public BEID_CertifStatus verifyCRL()
  {
    BEID_CertifStatus ret = (BEID_CertifStatus)beidlib_dotNetPINVOKE.BEID_Certificate_verifyCRL__SWIG_1(swigCPtr);
    if (beidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw beidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  /// <summary>Verify the certificate trough OCSP validation.</summary>
  public BEID_CertifStatus verifyOCSP()
  {
    BEID_CertifStatus ret = (BEID_CertifStatus)beidlib_dotNetPINVOKE.BEID_Certificate_verifyOCSP(swigCPtr);
    if (beidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw beidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

}

}
