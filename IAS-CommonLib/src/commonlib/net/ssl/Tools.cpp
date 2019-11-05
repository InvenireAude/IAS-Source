/*
 * File: IAS-CommonLib/src/commonlib/net/ssl/Tools.cpp
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
#include <commonlib/logger/logger.h>
#include <commonlib/memory/memory.h>
#include "Tools.h"
#include "SSLException.h"

#include <commonlib/exception/ItemNotFoundException.h>
#include <commonlib/exception/BadUsageException.h>

#include <commonlib/tools/MiscTools.h>
#include <string.h>

#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <openssl/md5.h>
#include <openssl/opensslv.h>

#ifndef OPENSSL_VERSION_NUMBER
#error "No open ssl ?"
#endif

#if OPENSSL_VERSION_NUMBER < 0x10101000L
#warning Using old openssl API (pre 1.1.1)
#define _IAS_OPENSSL_COMPAT
#endif

namespace IAS {
namespace Net {
namespace SSL {

/***********************************************************************/
String Tools::ComputeSHA256(const String& strValue){

	 IAS_TRACER;
	 unsigned char hash[SHA256_DIGEST_LENGTH];

	 SHA256_CTX sha256;

	 SHA256_Init(&sha256);
	 SHA256_Update(&sha256, strValue.c_str(), strValue.length());
	 SHA256_Final(hash, &sha256);

	 String strResult;
	 MiscTools::BinarytoHex(hash,SHA256_DIGEST_LENGTH,strResult);
	 return strResult;
}
/***********************************************************************/
String Tools::ComputeSHA256(const void *pData, size_t iDataLen){

	 IAS_TRACER;
	 unsigned char hash[SHA256_DIGEST_LENGTH];

	 SHA256_CTX sha256;

	 SHA256_Init(&sha256);
	 SHA256_Update(&sha256, pData, iDataLen);
	 SHA256_Final(hash, &sha256);

	 String strResult;
	 MiscTools::BinarytoHex(hash,SHA256_DIGEST_LENGTH,strResult);
	 return strResult;
}
/***********************************************************************/
String Tools::ComputeMD5(const String& strValue){
	 IAS_TRACER;

	 return ComputeMD5(strValue.c_str(), strValue.length());
}
/***********************************************************************/
String Tools::ComputeMD5(const void *pData, size_t iDataLen){

	 IAS_TRACER;
	 unsigned char hash[MD5_DIGEST_LENGTH];

	 MD5_CTX md5;

	 MD5_Init(&md5);
	 MD5_Update(&md5, pData, iDataLen);
	 MD5_Final(hash, &md5);

	 String strResult;
	 MiscTools::BinarytoHex(hash,MD5_DIGEST_LENGTH,strResult);
	 return strResult;
}
/***********************************************************************/
String Tools::ComputeSHA1(const String& strValue){

	 IAS_TRACER;
	 unsigned char hash[SHA_DIGEST_LENGTH];

	 SHA_CTX sha;

	 SHA1_Init(&sha);
	 SHA1_Update(&sha, strValue.c_str(), strValue.length());
	 SHA1_Final(hash, &sha);

	 String strResult;
	 MiscTools::BinarytoHex(hash,SHA_DIGEST_LENGTH,strResult);
	 return strResult;
}
/***********************************************************************/
String Tools::ComputeSHA1(const void *pData, size_t iDataLen){

	 IAS_TRACER;
	 unsigned char hash[SHA_DIGEST_LENGTH];

	 SHA_CTX sha;

	 SHA1_Init(&sha);
	 SHA1_Update(&sha, pData, iDataLen);
	 SHA1_Final(hash, &sha);

	 String strResult;
	 MiscTools::BinarytoHex(hash,SHA_DIGEST_LENGTH,strResult);
	 return strResult;
}
/***********************************************************************/
String Tools::ComputeHmacSHA256(const String& strKey, const void *pData, size_t iDataLen){

	 IAS_TRACER;
	 unsigned char hash[EVP_MAX_MD_SIZE];
	 unsigned int  iOutputLen;

	 if(HMAC(EVP_sha256(), strKey.c_str(), strKey.length(), (const unsigned char*)pData, iDataLen, hash, &iOutputLen) == NULL)
		 IAS_THROW(BadUsageException("ComputeHmacSHA256 has failed."));

	 String strResult;
	 MiscTools::BinarytoHex(hash,iOutputLen,strResult);
	 return strResult;
}
/***********************************************************************/
String Tools::ComputeHmacSHA256(const String& strKey, const String& strValue){

	 IAS_TRACER;
	 unsigned char hash[EVP_MAX_MD_SIZE];
	 unsigned int  iOutputLen;

	 if(HMAC(EVP_sha256(), strKey.c_str(), strKey.length(), (const unsigned char*)strValue.c_str(), strValue.length(), hash, &iOutputLen) == NULL)
		 IAS_THROW(BadUsageException("ComputeHmacSHA256 has failed."));

	 String strResult;
	 MiscTools::BinarytoHex(hash,iOutputLen,strResult);
	 return strResult;
}
/*************************************************************************/

/***********************************************************************/
Buffer* Tools::ComputeSignature(const PrivateKey* pKey, const String& strValue){

	 IAS_TRACER;

	 return ComputeSignature(pKey, strValue.c_str(), strValue.length());
}
/***********************************************************************/
#ifndef _IAS_OPENSSL_COMPAT
class MDHolder{
  public:
    MDHolder():md(0){
      this->md = EVP_MD_CTX_new();
    }

    ~MDHolder(){
      if(md)
        EVP_MD_CTX_free(md);
    }

    operator EVP_MD_CTX *(){
      return this->md;
    }

  protected:
    EVP_MD_CTX *md;
};
#endif
/***********************************************************************/
Buffer* Tools::ComputeSignature(const PrivateKey* pKey, const void *pData, size_t iDataLen){


	size_t iSignatureLen = 0;


#ifdef _IAS_OPENSSL_COMPAT
	EVP_MD_CTX md_ctx;
	EVP_MD_CTX *mdh = &md_ctx;
  EVP_MD_CTX_init(mdh);
#else
  MDHolder mdh;
#endif

	//SSL API revenge ...
    EVP_PKEY *pkey = const_cast<EVP_PKEY *>(pKey->getPrivateKey());

    IAS_CHECK_IF_NULL(pkey);

	if(!EVP_DigestSignInit(mdh, NULL, EVP_sha1(), NULL, pkey) ||
	   !EVP_DigestSignUpdate(mdh, pData, iDataLen))
		IAS_THROW(InternalException("Openssl error in EVP_DigestSignUpdate or EVP_DigestSignInit"));

	 if (!EVP_DigestSignFinal(mdh, NULL, &iSignatureLen))
		 IAS_THROW(InternalException("Openssl error in EVP_DigestSignFinal"));

	 if (iSignatureLen != EVP_PKEY_size(pkey))
		 IAS_THROW(InternalException("Openssl signature length error"));

	 IAS_DFT_FACTORY<Buffer>::PtrHolder ptrBuffer(IAS_DFT_FACTORY<Buffer>::Create(iSignatureLen));

	  if(!EVP_DigestSignFinal(mdh, ptrBuffer->getBuffer<unsigned char>(), &iSignatureLen))
		  IAS_THROW(InternalException("Openssl error in EVP_DigestSignFinal (2)"));

	  return ptrBuffer.pass();
}
/*************************************************************************/
static const EVP_MD *_dencodePBKDF2Algo(const String& strAlgo){

  if(!strAlgo.compare("SHA1"))
    return EVP_sha1();

  if(!strAlgo.compare("SHA256"))
    return EVP_sha256();

  if(!strAlgo.compare("SHA512"))
    return EVP_sha512();

 if(!strAlgo.compare("SHA3_512")){
#ifdef _IAS_OPENSSL_COMPAT
  IAS_THROW(BadUsageException("SHA3_512 is supported since openssl version 1.1.1"));
#else
    return EVP_sha3_512();
#endif
 }

  IAS_THROW(BadUsageException("Unknown PBKDF2 parameter, supported HMACs are[SHA1, SHA256, SHA512, SHA3_512]"));

}
/*************************************************************************/
String Tools::PBKDF2(
    const String& strAlgo,
    const String& strPassword,
    const String& strSalt,
    const unsigned long iCount,
    const unsigned long iResultSize) {

	  IAS_TRACER;

    const EVP_MD *algo = _dencodePBKDF2Algo(strAlgo);

	  unsigned int iDigestLength = SHA_DIGEST_LENGTH;

    unsigned char mdValue[EVP_MAX_MD_SIZE];
	  unsigned char mdWork[EVP_MAX_MD_SIZE];

    unsigned long iCounter = 1;
	  unsigned long iGeneratedSize = 0;

    unsigned char output[iResultSize];

    size_t iSaltLength = strSalt.length();
    unsigned char salt[iSaltLength + 4];

    const unsigned char* password = (unsigned char*)strPassword.c_str();
    size_t iPasswordLength = strPassword.length();

    memcpy(salt, strSalt.c_str(), iSaltLength);

	  while (iGeneratedSize < iResultSize) {

      size_t iTmp = iSaltLength;

      salt[iTmp++] = (iCounter >> 24) & 0xff;
      salt[iTmp++] = (iCounter >> 16) & 0xff;
      salt[iTmp++] = (iCounter >> 8) & 0xff;
      salt[iTmp++] = (iCounter >> 0) & 0xff;

      HMAC(algo, password, iPasswordLength, salt, iSaltLength + 4, mdValue, &iDigestLength);

      memcpy(mdWork, mdValue, iDigestLength);

      for (int iIdx = 2; iIdx <= iCount; iIdx++) {
        HMAC(algo, password, iPasswordLength, mdValue, iDigestLength, mdValue, &iDigestLength);

        for (unsigned long iByte = 0; iByte < iDigestLength; iByte++) {
          mdWork[iByte] ^= mdValue[iByte];
        }

      }

      unsigned long iBytes = (iResultSize - iGeneratedSize < iDigestLength) ? (iResultSize - iGeneratedSize) : iDigestLength ;
      memcpy(output + iGeneratedSize, mdWork, iBytes);
      iGeneratedSize += iBytes;
      ++iCounter;
    }

    String strResult;
    MiscTools::BinaryToBase64(output, iResultSize, strResult);
    return strResult;
}

}
}
}
