/*
 * File: IAS-QSystemExe/src/parameters/MBusRepeaterParameters.h
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
#ifndef _IAS_QS_Parameters_MBusRepeaterParameters_H_
#define _IAS_QS_Parameters_MBusRepeaterParameters_H_

#include "ProgramParameters.h"

namespace IAS {
namespace Exe {
namespace Parameters {

/*************************************************************************/
/** The MBusRepeaterParameters class.
 *
 */
class MBusRepeaterParameters : public ::IAS::Exe::Parameters::ProgramParameters{
public:

	virtual ~MBusRepeaterParameters() throw();

  int     getPort()const;

  const String& getInterface()const;
  const String& getGroup()const;
  const String& getDumpDirectory()const;
  bool hasDumpDirectory()const;

  int getInputBufferSize()const;
  int getOutputBufferSize()const;
  int getMaxPacketSize()const;
  int getNumThreads()const;

  int getMaxFileSize()const;
  int getMaxPacketsInFile()const;
  int getNewFileInterval()const;

protected:
	MBusRepeaterParameters(int argc, char* argv[]);

	virtual void printCmdDesc(std::ostream& os) const;
	virtual void printArgsDesc(std::ostream& os) const;

	friend class ::IAS::Factory<MBusRepeaterParameters>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_SM_CmdLine_MBusRepeaterParameters_H_ */
