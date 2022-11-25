#include "cloosemountpath.h"
#include "cloosefile.h"
#include <cassert>

CLooseMountPath::CLooseMountPath(std::string path)
{
    this->dirHandle = std::filesystem::directory_entry{path};
    assert(dirHandle.is_directory());
    this->filePath = path;

}

std::vector<std::shared_ptr<IFile>> CLooseMountPath::Find(std::string substr)
{
    using namespace std::filesystem;
    const path rootPath = dirHandle.path();
    std::vector<std::shared_ptr<IFile>> results;

    for (const auto& file:recursive_directory_iterator{rootPath}) {
        if (file.is_regular_file()&&file.path().generic_string().find(substr)!=std::string::npos) {
            std::filesystem::path relPath;
            relPath = std::filesystem::relative(file.path(),this->filePath);
            std::shared_ptr<IFile> fileHandle = std::make_shared<CLooseFile>(CLooseFile(this->filePath,relPath.generic_string()));
            results.push_back(fileHandle);
        }
    }

    return results;


}

void CLooseMountPath::ListFiles(std::vector<std::string> &files)
{
  using std::filesystem::recursive_directory_iterator;
  using std::filesystem::is_directory;
  for (recursive_directory_iterator i(filePath), end; i != end; ++i)
      if (!is_directory(i->path()))
        files.emplace_back(i->path().filename());
}


