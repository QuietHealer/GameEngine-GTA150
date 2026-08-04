#include "engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"
#include "SpaceGame.h"

#include <iostream>
#include <vector>
#include <Scene.h>
#include <map>
#include <memory>


using namespace nu;

class Object
{
public:
    Object() { std::cout << "constructor\n"; }
    ~Object() { std::cout << "destructor\n"; }

    Object(const Object& object) { std::cout << "copy\n"; }
    Object& operator = (const Object& object) { std::cout << "assignment\n"; return *this; }
};

int main()
{
    /*
    std::map<std::string, int> students;
    students["Aiden"] = 16;
    students["Jack"] = 17;
    students["River"] = 15;
        
    std::cout << students["Aiden"] << std::endl;

    // get current working directory
    std::cout << "Directory Operations:\n";
    std::cout << "Working directory: " << nu::GetWorkingDirectory() << "\n";

    // set working directory (current working directory + "Assets")
    std::cout << "Setting directory to 'Assets'...\n";
    nu::SetWorkingDirectory("Assets");
    std::cout << "New directory: " << nu::GetWorkingDirectory() << "\n\n";

    // get filenames in the working directory
    std::cout << "Files in Directory:\n";
    auto filenames = nu::GetFilesInDirectory(nu::GetWorkingDirectory());
    for (const auto& filename : filenames)
    {
        std::cout << filename << "\n";
    }
    std::cout << "\n";

    // get filename info
    if (!filenames.empty())
    {
        // get filename
        std::string str = nu::GetFilename(filenames[0]);
        std::cout << "Filename: " << str << "\n";

        // get extension
        str = nu::GetFileExtension(filenames[0]);
        std::cout << "Extension: " << str << "\n";

        // get filename no extension
        str = nu::GetFilenameNoExtension(filenames[0]);
        std::cout << "Filename No Extension: " << str << "\n\n";
    }

    // read and display text file
    std::cout << "Text File Reading:\n";
    std::string str;
    if (nu::ReadTextFile("test.txt", str))
    {
        std::cout << str << "\n";
    }

    // write to text file
    std::cout << "Text File Writing:\n";
    nu::WriteTextFile("test.txt", "Hello, World!", true);
    if (nu::ReadTextFile("test.txt", str))
    {
        std::cout << str << "\n";
    }
    */

    std::cout << "============odject============\n";
    {
        Object objectA;
        Object objectB(objectA);
        Object objectC;
        objectC = objectA;

    }

    std::cout << "============raw pointers============\n";
    {
        Object* objectA = new Object();
        std::cout << objectA << std::endl;
        Object* objectB = new Object(*objectA);
        std::cout << objectB << std::endl;
        Object* objectC =nullptr;
        objectC = objectA;
        std::cout << objectC << std::endl;


        delete objectA;
        delete objectB;
        //delete objectC;

    }

    std::cout << "============smart pointers============\n";
    {
        std::unique_ptr<Object> objectA = std::make_unique<Object>();
        std::cout << objectA.get() << std::endl;
        std::unique_ptr<Object> objectB;
        objectB = std::move(objectA);
        std::cout << objectB.get() << std::endl;

        objectB.reset();
    }

    //return 0;

    SetWorkingDirectory("assets");
    // INITALIZATION
    Engine::Get().Initialize();

    SpaceGame game;
    game.Initialize();

    // create audio system
    FMOD::System* audio;
    FMOD::System_Create(&audio);

    void* extradriverdata = nullptr;
    audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

    std::vector<FMOD::Sound*> sounds;

    FMOD::Sound* sound = nullptr;

    Engine::Get().GetAudio().AddSound("sound", "audio/whistle.mp3");

    // create texture, using shared_ptr so texture can be shared
    std::shared_ptr<Texture> texture = std::make_shared<Texture>();
    texture->Load("textures/spaceship_BLUE.png", Engine::Get().GetRenderer());

    // MANE LOOP
    bool quit = false;
    while (!quit) 
    {

        SDL_Event event;
        while (SDL_PollEvent(&event)) 
        {
            if (event.type == SDL_EVENT_QUIT) 
            {
                quit = true;
            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE)
            {
                quit = true;
            }
        }

        // UPDATE
        Engine::Get().Update();

        float dt = Engine::Get().GetTime().GetDeltaTime();

        game.Update(dt);
        audio->update();

        // DRAW
        Engine::Get().GetRenderer().SetColor(0.0f, 0.0f, 0.0f);
        Engine::Get().GetRenderer().Clear();

        Engine::Get().GetRenderer().DrawTexture(texture.get(), 0.0f, 0.0f);
        game.Draw(Engine::Get().GetRenderer());
        Engine::Get().GetPS().Draw(Engine::Get().GetRenderer());

        Engine::Get().GetRenderer().Present();
    }

    Engine::Get().Shutdown();
    
    return 0;
}

