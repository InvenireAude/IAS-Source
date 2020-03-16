/*
 * File: IAS-CommonLib/src/commonlib/tools/Version.cpp
 *
 * Copyright (C) 2019, Albert Krzymowski
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
#include "Version.h"

#include <openssl/opensslv.h>

namespace IAS {
namespace Lang {
void Version::Print(std::ostream& os){

  const String CVersion ("2.2.2");

  os<<"IAS Script:   "<<CVersion<<std::endl;
  os<<" Complied on: "<<__DATE__<<" "<<__TIME__<<", environment: "<<__VERSION__<<std::endl;

}
}
/*************************************************************************/
}
