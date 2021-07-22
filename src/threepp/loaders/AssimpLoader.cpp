
#include "threepp/loaders/AssimpLoader.hpp"

#include <assimp/Importer.hpp> // C++ importer interface
#include <assimp/postprocess.h>// Post processing flags
#include <assimp/scene.h>      // Output data structure

#include "threepp/objects/Mesh.hpp"
#include "threepp/materials/MeshBasicMaterial.hpp"

using namespace threepp;

namespace {

    std::vector<float> copyVertices(int numVertices, aiVector3D* aVertices) {

        std::vector<float> properties(numVertices*3);

        for (int i = 0; i < numVertices; i++) {
            auto v = aVertices[i];
            properties.emplace_back(v.x);
            properties.emplace_back(v.y);
            properties.emplace_back(v.z);
        }

        return properties;
    }

}

std::shared_ptr<Group> AssimpLoader::load(const std::string &path) {

    Assimp::Importer importer;

    const aiScene *aScene = importer.ReadFile(path,
                                             aiProcess_CalcTangentSpace |
                                                     aiProcess_Triangulate |
                                                     aiProcess_JoinIdenticalVertices |
                                                     aiProcess_SortByPType);

    auto group = Group::create();

    const int numMeshes = aScene->mNumMeshes;
    for (int i = 0; i < numMeshes; i++) {

        auto geometry = BufferGeometry::create();

        auto aMesh = aScene->mMeshes[i];
        if (aMesh->HasPositions()) {
            std::vector<float> vertices = copyVertices(aMesh->mNumVertices, aMesh->mVertices);
            geometry->setAttribute("position", FloatBufferAttribute::create(vertices, 3));

            if (aMesh->HasNormals()) {
                std::vector<float> normals = copyVertices(aMesh->mNumVertices, aMesh->mNormals);
                geometry->setAttribute("normal", FloatBufferAttribute::create(normals, 3));
            }

        }

        auto material = MeshBasicMaterial::create();

        auto mesh = Mesh::create(geometry, material);

        group->add(mesh);
    }

    return group;

}
