
#include "threepp/threepp.hpp"

#include "threepp/loaders/AssimpLoader.hpp"

using namespace threepp;

int main() {

    Canvas canvas;

    auto scene = Scene::create();
    auto camera = PerspectiveCamera::create(75, canvas.getAspect(), 0.1f, 1000);
    camera->position.z = 5;

    auto renderer = GLRenderer(canvas);
    renderer.checkShaderErrors = true;
    renderer.setClearColor(Color(Color::aliceblue));
    renderer.setSize(canvas.getSize());

    AssimpLoader loader;
    auto group = loader.load("models/obj/walt/WaltHead.obj");

    scene->add(group);

    canvas.onWindowResize([&](WindowSize size){
      camera->aspect = size.getAspect();
      camera->updateProjectionMatrix();
      renderer.setSize(size);
    });

    canvas.animate([&](float dt) {

      renderer.render(scene, camera);
    });


}