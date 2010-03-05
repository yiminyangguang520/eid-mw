/* ****************************************************************************

 * eID Middleware Project.
 * Copyright (C) 2008-2010 FedICT.
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
#ifndef _ANALYSEMETA_H_
#define _ANALYSEMETA_H_

#include <map>
#include "analysis.h"
#include "Repository.h"
#include "MetaRule.h"
#include "MetaRuleVerdict.h"
#include "WinSCardDllLocksRule.h"
#include "HPProtectToolsRule.h"
#include "MiddleWareFilesIntegrityRule.h"

typedef std::multimap<double,MetaRule*> MetaRuleMap;

class AnalyseMeta : public Analysis
{
public:
	AnalyseMeta()
	:m_rules()
	{
		m_testName = "diagnostics";
		m_friendlyName = "Diagnostics";

		m_rules.insert(make_pair(	.5,	new MiddleWareFilesIntegrityRule()));	// are middleware files all present and intact?
#ifdef WIN32
		m_rules.insert(make_pair(	.5,	new WinSCardDllLocksRule()));			// winscard.dll locked by unexpected processes?
		m_rules.insert(make_pair(	.5,	new HPProtectToolsRule()));				// HP ProtectTools ("ActivCard") running?
#endif
	}

	virtual ~AnalyseMeta()
	{
	}

	virtual int run()
	{
		int retVal = DIAGLIB_OK;
		m_bPassed = true;
		setProgress(0);
		setStartTime();

		try
		{
			progressInit(1);

			reportPrintHeader2(REPORT_TYPE_RESULT, L"Meta Diagnostics",L'#');

			// reverse iterator on rules, so we get rules high before rules with low weights
			for(MetaRuleMap::const_reverse_iterator rule=m_rules.rbegin();rule!=m_rules.rend();rule++)
			{
				REP_PREFIX(rule->second->name());

				try
				{
					MetaRuleVerdict verdict=rule->second->verdict(REPOSITORY);
					if(verdict.guilty())
					{
						resultToReport(REPORT_TYPE_RESULT,(rule->second->name() + L":Established Diagnosis:").	c_str());
						resultToReport(REPORT_TYPE_RESULT,verdict.verdict().									c_str());
						resultToReport(REPORT_TYPE_RESULT,verdict.corrective().									c_str());
						REP_AVAILABLE(true);
						REP_CONTRIBUTE(L"diagnosis",L"true");
					}
					else
					{
						resultToReport(REPORT_TYPE_RESULT,(rule->second->name() + L":Fine").c_str());
						REP_AVAILABLE(true);
						REP_CONTRIBUTE(L"diagnosis",L"false");
					}
				}
				catch(...)	// Sweeping catch so whatever rules do the exceptions end here.
				{
					resultToReport(REPORT_TYPE_RESULT,(rule->second->name() + L":Failed To Run").c_str());
					REP_AVAILABLE(false);
				}

				REP_UNPREFIX();
			}

			reportPrintHeader2(REPORT_TYPE_RESULT, L"Meta Diagnostics Raw Data",L'#');
			ContributionMap contributions=REP_RESULTS();
			for(ContributionMap::const_iterator i=contributions.begin();i!=contributions.end();i++)
			{
				std::wstring	contribStr(i->first);
								contribStr.append(L"=");
								contribStr.append(i->second);
				commentToReport(REPORT_TYPE_RESULT,contribStr.c_str());
			}
				
			progressIncrement();
		}
		//------------------------------------------
		// exception from writing to the report
		//------------------------------------------
		catch (ExcReport& exc) 
		{
			processParamsToStop();
			retVal = exc.getErr();
		}
		resultToReport(REPORT_TYPE_RESULT,m_bPassed);
		progressRelease();
		return retVal;
	}

private:
	MetaRuleMap m_rules;
};

#endif
