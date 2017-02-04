#include <SFML/Audio.hpp>
#include <iostream>
#include <string>


sf::Music music;
sf::SoundBuffer soundBuffer;
sf::Sound sound;

bool initAudio()
{
    if (!music.openFromFile("music/LOL.wav"))
        return false;
    if (!soundBuffer.loadFromFile("music/don.wav"))
        return false;

    sound.setBuffer(soundBuffer);

    return true;
}


void playm()
{
    music.play();

    while (music.getStatus() == sf::Music::Playing)
    {
        sf::sleep(sf::seconds(100));    // Reduce CPU time

        /*
        // Display the playing position
        std::cout << "\rPlaying... " << music.getPlayingOffset().asSeconds() << " sec        ";
        std::cout << std::flush;
        */
    }


}
void plays()
{
    sound.play();
}

sf::Thread threadm(&playm);
sf::Thread threads(&plays);


void playMusic()
{
    threadm.launch();

}
void playSound()
{
    threads.launch();
}
