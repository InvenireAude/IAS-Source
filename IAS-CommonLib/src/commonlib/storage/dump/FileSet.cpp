/*
 * File: FileSet.cpp
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

#include "FileSet.h"
#include <commonlib/tools/TypeTools.h>
#include <commonlib/tools/MiscTools.h>
#include <commonlib/sys/fs/DirectoryReader.h>

namespace IAS {
namespace Storage {
namespace Dump {

const String FileSet::CFileSufix(".dat");
const int    FileSet::CNumNameDigits(10);
/*************************************************************************/
FileSet::FileSet(const String& strDirectory,
                size_t   iMaxFileSize):
  strDirectory(strDirectory),
  iNextSeq(0),
  iMaxFileSize(iMaxFileSize){
	IAS_TRACER;

  if(!discoverNextSequence()){
    createNewFile();
  }

  IAS_LOG(LogLevel::INSTANCE.isInfo(),"DumpFileSet: "<<strDirectory<<", next squence: "<<this->iNextSeq);

}
/*************************************************************************/
FileSet::~FileSet() throw(){
	IAS_TRACER;

  for(FilesList::iterator it = lstFiles.begin(); it != lstFiles.end(); it++){
    IAS_DFT_FACTORY<File>::Free(*it);
    it = lstFiles.erase(it);
  }

  for(FilesList::iterator it = lstBackLogFiles.begin(); it != lstBackLogFiles.end(); it++){
    IAS_DFT_FACTORY<File>::Free(*it);
    it = lstBackLogFiles.erase(it);
  }


}
/*************************************************************************/
bool FileSet::discoverNextSequence(){
  IAS_TRACER;

  IAS_DFT_FACTORY<SYS::FS::DirectoryReader>::PtrHolder ptrDirectoryReader(
    IAS_DFT_FACTORY<SYS::FS::DirectoryReader>::Create(strDirectory)
  );

  ptrDirectoryReader->read();

  for(SYS::FS::DirectoryReader::const_reverse_iterator it = ptrDirectoryReader->rbegin();
      it != ptrDirectoryReader->rend(); it++){
        const String& strFileName((*it)->strFile);
        if(strFileName.length() == CNumNameDigits + CFileSufix.length() &&
           strFileName.substr(CNumNameDigits).compare(CFileSufix) == 0){

          iNextSeq = TypeTools::StringToLong(strFileName.substr(0,CNumNameDigits));
          lstFiles.push_front(IAS_DFT_FACTORY<File>::Create(buildFileName(iNextSeq)));
          iNextSeq++;

          IAS_LOG(LogLevel::INSTANCE.isInfo(),"Next sequence discovery: "<<iNextSeq);
          return true;
        }

      }

  return false;
}
/*************************************************************************/
void FileSet::createNewFile(){
  IAS_TRACER;
  String strFileName(buildFileName(this->iNextSeq++));
  lstFiles.push_front(IAS_DFT_FACTORY<File>::Create(strFileName, iMaxFileSize));
}
/*************************************************************************/
void FileSet::openBackLog(){
  IAS_TRACER;

  IAS_LOG(LogLevel::INSTANCE.isInfo(),"Opening BackLog.");

  IAS_DFT_FACTORY<SYS::FS::DirectoryReader>::PtrHolder ptrDirectoryReader(
    IAS_DFT_FACTORY<SYS::FS::DirectoryReader>::Create(strDirectory)
  );

  ptrDirectoryReader->read();

  for(SYS::FS::DirectoryReader::const_iterator it = ptrDirectoryReader->begin();
      it != ptrDirectoryReader->end(); it++){
        if( (*it)->strFile.find(String(".dat")) != String::npos)
          lstBackLogFiles.push_back(IAS_DFT_FACTORY<File>::Create(strDirectory + "/" + (*it)->strFile));
      }

  itBackLogFiles = lstBackLogFiles.begin();

 IAS_LOG(LogLevel::INSTANCE.isInfo(),"BackLog size: "<<lstBackLogFiles.size());

}
/*************************************************************************/
void *FileSet::nextFromBackLog(File::SizeType& iDataLen){

  while(itBackLogFiles != lstBackLogFiles.end() && !(*itBackLogFiles)->hasMoreData()){
    IAS_LOG(LogLevel::INSTANCE.isInfo(),"BackLog done for: "<<(*itBackLogFiles)->getName());
    itBackLogFiles++;
  }

  return (*itBackLogFiles)->readNext(iDataLen);
}
/*************************************************************************/
bool FileSet::hasMoreBackLogData(){

  while(itBackLogFiles != lstBackLogFiles.end() && !(*itBackLogFiles)->hasMoreData()){
     IAS_LOG(LogLevel::INSTANCE.isInfo(),"BackLog done for: "<<(*itBackLogFiles)->getName());
    itBackLogFiles++;
  }

  IAS_LOG(LogLevel::INSTANCE.isInfo(),"hasMoreBackLogData: "<<(itBackLogFiles != lstBackLogFiles.end()));

  return itBackLogFiles != lstBackLogFiles.end();
}
/*************************************************************************/
void FileSet::closeOldest(){
  IAS_DFT_FACTORY<File>::Free(lstFiles.back());
  lstFiles.pop_back();
}
/*************************************************************************/
String FileSet::buildFileName(unsigned int iSeq)const{
  StringStream ssName;
  ssName<<strDirectory<<"/"<<TypeTools::IntToString(iSeq++,CNumNameDigits)<<CFileSufix;
  return ssName.str();
}
/*************************************************************************/
void* FileSet::allocate(size_t n){
	IAS_TRACER;

  if(lstFiles.size() == 0 || lstFiles.front()->getFree() < n ){
    createNewFile();
  }

  return lstFiles.front()->allocate(n);
}
/*************************************************************************/
void  FileSet::free(const void* p){
}
/*************************************************************************/
bool  FileSet::check(const void* p){
  //TODO check
  return true;
}
/*************************************************************************/
void  FileSet::trim(){
}
/*************************************************************************/
void FileSet::printToStream(std::ostream& os){
}
/*************************************************************************/
void FileSet::dumpBackLogInfo(std::ostream& os){

  os<<"\tFile\tItems\tAllocated / Size"<<std::endl;
  for(FilesList::const_iterator it = lstBackLogFiles.begin();
      it != lstBackLogFiles.end(); it++){
        os<<"\t"<<(*it)->getName()<<"\t"<<(*it)->getNumItems()<<"\t"<<(*it)->getAllocated()<<" / "<<(*it)->getSize()<<std::endl;
      }
  os<<std::endl;
}
/*************************************************************************/
}
}
}
