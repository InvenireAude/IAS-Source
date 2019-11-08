/*
 * File: IAS-CommonLib/src/commonlib/tools/Version.h
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
#ifndef _IAS_Lang_Version_H_
#define _IAS_Lang_Version_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace Lang {
/*************************************************************************/
/** The Version class.
 *
 */
class Version {
public:

	static void Print(std::ostream& os);

};

/*************************************************************************/
}
}
#endif /* _IAS_Lang_Version_H_ */
