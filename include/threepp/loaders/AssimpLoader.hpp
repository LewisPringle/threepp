
#ifndef THREEPP_ASSIMPLOADER_HPP
#define THREEPP_ASSIMPLOADER_HPP

#include "threepp/objects/Group.hpp"

#include <string>

namespace threepp {

    class AssimpLoader {

    public:

        std::shared_ptr<Group> load(const std::string &path);

    };

}

#endif//THREEPP_ASSIMPLOADER_HPP
