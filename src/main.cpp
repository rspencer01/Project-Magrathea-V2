#include <game.h>

void runConsole(Game*);

/// The main function, called first on execution.
///
/// @param argc The number of command line arguments
/// @param argv The values of the command line arguments
int main(int argc, char** argv)
{
  // Are we running in console mode?
  bool textMode = false;
  // Check to see if the command line paramter for console mode is present
  if (argc>0)
    if (argv[1][0]=='-' && argv[1][1]=='c')
      textMode = true;
  // Construct a game and initialise it
  Game mainGame(!textMode);
  if (textMode==false)
  {
    // Run the game
    mainGame.run();
  }
  else
  {
    runConsole(&mainGame);
  }
  return 0;
}
