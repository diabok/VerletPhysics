#include <iostream>

#include "engine/window_context_handler.hpp"
#include "engine/common/number_generator.hpp"
#include "engine/common/color_utils.hpp"
#include "physics//physics.hpp"
#include "thread_pool/thread_pool.hpp"
#include "renderer/renderer.hpp"

int main()
{
    const uint32_t window_width = 1920;
    const uint32_t window_height = 1080;
    WindowContextHandler app("Verlet", sf::Vector2u(window_width, window_height), sf::Style::Default);
    RenderContext& render_context = app.getRenderContext();



    tp::ThreadPool thread_pool(16);
    const IVec2 world_size{960, 540};
    PhysicSolver solver{world_size, thread_pool};
    Renderer renderer(solver, thread_pool);

    const float margin = 20.0f;
    const auto zoom = static_cast<float>(window_height - margin) / static_cast<float>(world_size.y);
    render_context.setZoom(zoom);
    render_context.setFocus({world_size.x * 0.5f, world_size.y * 0.5f});

    bool emit = true;
    app.geteEventManager().addKeyPressedCallback(sf::Keyboard::Space, [&](sfev::CstEv) {
        emit = !emit;
    });

    constexpr uint32_t fps_cap = 120;
    int32_t target_fps = fps_cap;
    app.geteEventManager().addKeyPressedCallback(sf::Keyboard::S, [&](sfev::CstEv){
        target_fps = target_fps ? 0 : fps_cap;
        app.setFramerateLimit(target_fps);
    } );


    //Main loop`
    const float dt = 1.0f / static_cast<float>(fps_cap);
    while(app.run()) {
        if(solver.objects.size() < 60000 && emit)
        {

            for (uint32_t i{10}; i--;)
            {
                const auto id = solver.createObject({2.0f, 10.0f + 1.1f * i});
                if(i == 0 || i == 9)
                {solver.objects[id].last_position.x -= 0.5f;
                 solver.objects[id].acceleration.x += 0.1f;
                }
                else {
                    solver.objects[id].last_position.x -= 0.2f;
                }
                solver.objects[id].color = ColorUtils::getRainbow(id * 0.001f);

            }
        }
        if(solver.objects.size() < 50000 && emit)
        {

            for (uint32_t i{10}; i--;)
            {
                const auto id = solver.createObject({2.0f, 100.0f + 1.1f * i});
                if(i == 0 || i == 9)
                {solver.objects[id].last_position.x -= 0.6f;
                 solver.objects[id].acceleration.x += 0.1f;
                }
                else {
                    solver.objects[id].acceleration.x += 0.8f;
                    solver.objects[id].last_position.x -= 0.2f;
                }
                solver.objects[id].color = ColorUtils::getRainbow(id * 0.01f);

            }
        }

        solver.update(dt);
        render_context.clear();
        renderer.render(render_context);
        render_context.display();

    }
    return EXIT_SUCCESS;
}
