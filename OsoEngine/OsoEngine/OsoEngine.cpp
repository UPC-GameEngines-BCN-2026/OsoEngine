#include "OsoEngine.h"
#include <glm/glm.hpp>


using namespace std;

int main()
{
    glm::vec3 position(1.0f, 2.0f, 3.0f);

    std::cout << "OsoEngine iniciado!\n";
    std::cout << "Position: "
        << position.x << ", "
        << position.y << ", "
        << position.z << "\n";

    return 0;
}
