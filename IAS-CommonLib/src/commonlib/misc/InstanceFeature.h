/*
 * File: IAS-CommonLib/src/commonlib/misc/InstanceFeature.h
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
#ifndef _IAS_InstanceFeature_H_
#define _IAS_InstanceFeature_H_

/*
 *
 */

#include "../memory/ma/Factory.h"
#include "../threads/Mutex.h"

namespace IAS {

template<class TT>
class InstanceFeature {
public:

	//TODO (L?) throw()
	virtual ~InstanceFeature(){};

	static TT* GetInstance() {
		//TODO (L) Analyze Mutex::Locker locker(TheMutex) - is it up to the user to initialize safely.
		if(!TheInstance)
			TheInstance = ::IAS::StandardFactory< TT >::Create();
		return TheInstance;
	}

	/*
	 * For debug purposes only.
	 */

	static void Delete() {
    if(TheInstance)
         ::IAS::StandardFactory< TT >::Free(TheInstance);
    TheInstance = 0;
    }


protected:
	typedef TT* TheInstanceType;
	static TheInstanceType TheInstance;
};

template<class TT>
 typename InstanceFeature<TT>::TheInstanceType InstanceFeature<TT>::TheInstance(0);

template<class F , class T>
class InstanceFeatureWithFactory {
public:

	virtual ~InstanceFeatureWithFactory(){};

	static T* GetInstance() {
		if(!TheInstance)
			TheInstance = F::Create();
		return TheInstance;
	}

	/*
	 * For debug purposes only.
	 */

	static void Delete() { F::Free(TheInstance); }

protected:

	typedef T* TheInstanceType;
	static TheInstanceType TheInstance;
};

template<class F, class T>
typename InstanceFeatureWithFactory<F,T>::TheInstanceType InstanceFeatureWithFactory<F,T>::TheInstance(0);


}

#endif /* INSTANCEFEATURE_H_ */
