#include <SFML/Graphics.hpp>
#include "Framework/Framework.h"
#include "Framework/ResourceMgr.h"
#include "GameObject/Player.h"

int main()
{
    FRAMEWORK->Init(1920, 1080);
    FRAMEWORK->Do();

    return 0;
}