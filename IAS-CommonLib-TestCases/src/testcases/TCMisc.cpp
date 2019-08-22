/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCMisc.cpp
 *
 * Copyright (C) 2015, Albert Krzymowski
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "commonlib/commonlib.h"

#include "TCMisc.h"
#include <unistd.h>

namespace IAS{
namespace TCT{

/*************************************************************************/

TCMisc::TCMisc(TestSuite* pTestSuite):theTestRunner(this){
	IAS_TRACER;
	init(pTestSuite);
}

/*************************************************************************/

TCMisc::~TCMisc() throw(){
	IAS_TRACER;
}

/*************************************************************************/
void TCMisc::init(TestSuite* pTestSuite){
	IAS_TRACER;
	//theTestRunner.addCase("ALL",&::IAS::TCT::TCMisc::caseALL);
	theTestRunner.addCase("Base64",&::IAS::TCT::TCMisc::caseBase64);
  theTestRunner.addCase("Decimal",&::IAS::TCT::TCMisc::decimal);
	TestUnit::init("TCMisc",&theTestRunner,pTestSuite);
}
/*************************************************************************/
void TCMisc::caseALL(){

	IAS_TRACER;
	std::cout<<IAS::MiscTools::StrToHex("\033AB\n\r\n\003abąło")<<'\n';
	std::cout<<IAS::MiscTools::StrToPrintableAndHex("\033AB\n\r\n\003abąło")<<'\n';
	std::cout<<IAS::MiscTools::StrToPrintableOrHex("\033AB\n\r\n\003abąło")<<'\n';

	std::cout<<TypeTools::Replace("abc1234abc56789abc","abc","XYZ")<<'\n';
	std::cout<<TypeTools::Replace("1234abc56789","abc","XYZ")<<'\n';

	{

		String strPattern("${home} sweet ${HOME}");
		String strValue = EnvTools::Substitute(strPattern);

		if(strValue.compare(" sweet "+EnvTools::GetEnv("HOME")) != 0)
			IAS_THROW(InternalException("Test case failed for  EnvTools::Substitute"));

		std::cout<<"Value: "<<strValue<<std::endl;

	}

	TimeSamplesResults tsr;
	TimeSample ts(true);
	std::cout<<"Wait !"<<std::endl;
	sleep(1);
	tsr.addSample(ts);
	sleep(2);
	tsr.addSample(ts);
	std::cout<<tsr<<std::endl;

}
/*************************************************************************/
void TCMisc::caseBase64(){
	IAS_TRACER;

	String s("ABCDEFGHIJKL");

	unsigned char buffer[1024];
	String strBase64;
	String strOutput;
	size_t iDataLen;

	IAS::MiscTools::BinaryToBase64((const unsigned char*)s.c_str(), s.length()+1, strBase64);
	std::cout<<strBase64<<'\n';
	std::cout<<strOutput<<'\n';
	IAS::MiscTools::Base64ToBinary(strBase64, buffer, 1024, iDataLen);
	IAS::MiscTools::Base64ToString(strBase64, strOutput);

	std::cout<<s.length()<<":"<<iDataLen<<'\n';

	std::cout<<strOutput<<'\n';
	String str2((const char*)buffer,iDataLen-1);
	std::cout<<str2<<'\n';
}
/*************************************************************************/
void TCMisc::decimal(){
	IAS_TRACER;

	Decimal d1("+123.4");
  Decimal d2(123.456);
  Decimal d3(-1234.56);

 // std::cout<<"Decimal:"<<d1<<" "<<d2<<" "<<d3<<std::endl;
 // std::cout<<"Decimal2:"<<(Float)d2<<" "<<(long)d2<<" "<<d2.toString()<<std::endl;
 // std::cout<<"Decimal3:"<<(d2+d3)<<std::endl;
 // std::cout<<"Decimal3:"<<(Decimal)100<<" "<<(d2+(Decimal)100)<<std::endl;

	if((d2+(Decimal)100).toString().compare("223.45") != 0)
			IAS_THROW(InternalException("Test case failed for test case: Decimal [01]"));

	if((d2-(Decimal)100).toString().compare("23.45") != 0)
			IAS_THROW(InternalException("Test case failed for test case: Decimal [02]"));

	if((d2*(Decimal)10).toString().compare("1234.50") != 0)
			IAS_THROW(InternalException("Test case failed for test case: Decimal [03]" + (d2*(Decimal)10).toString()));

	if((d2/(Decimal)-10).toString().compare("-12.34") != 0)
			IAS_THROW(InternalException("Test case failed for test case: Decimal [04]" + (d2/(Decimal)-10).toString()));

	if(d1 == d2)
			IAS_THROW(InternalException("Test case failed for test case: Decimal [05]"));

	if(d1 != Decimal("123.40"))
			IAS_THROW(InternalException("Test case failed for test case: Decimal [06]" + d1.toString() + " ? 123.40"));

	if(!(d1 != Decimal("123.41")))
			IAS_THROW(InternalException("Test case failed for test case: Decimal [07]" + d1.toString() + " ? 123.41"));


}
/*************************************************************************/
} /* namespace TCT */
} /* namespace IAS */
