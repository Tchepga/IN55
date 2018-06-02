#ifndef HELPERS_H
#define HELPERS_H
#include <GL/glew.h>

class Helpers
{
    public:
        Helpers();
        virtual ~Helpers();
        void ComputeQuatW( glm::quat& quat );
    protected:

    private:
};

#endif // HELPERS_H
