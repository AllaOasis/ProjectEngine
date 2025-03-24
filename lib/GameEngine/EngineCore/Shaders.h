#ifndef SHADERS_H
#define SHADERS_H

namespace GameEngine
{
    class Shaders
    {
    private:
        static const char* get_fragment_source();
        static const char* get_vertex_source();

    public:
        static unsigned int create_program(bool debug = false);
    };
}

#endif // SHADERS_H