
enum Roles {PAWN, KING, KNIGHT, WIZARD};
byte Role = PAWN;

enum Teams {WHITETEAM, BLACKTEAM};
byte Team = WHITETEAM;

enum signalState {SETUP, START, PLAY};
// Then a byte to hold the current state.
byte signalState = SETUP;

#define BLACKOUT makeColorHSB(0,0,0)

void setup() 
{
  // put your setup code here, to run once:
}

void loop() 
{
  switch(signalState)
  {
  case SETUP:
    setupLoop();
    break;

  case START:
    startLoop();
    break;

  case PLAY:
    playLoop();
    break;
  }

  displayRole();

  byte sendData = (Role << 2) + (signalState);
  setValueSentOnAllFaces(sendData);
}

void setupLoop()
{
  
  if(buttonSingleClicked())
  {
    Role = KING;
    signalState = START;
  }

    bool foundKing = false;

    // CHECK FOR START SIGNAL
  FOREACH_FACE(f)
  {
    // IF WE DETECT A NEIGHBOR!
    if(!isValueReceivedOnFaceExpired(f))
    {
      // IF MY NEIGHBOR'S FACE IS SAYING START, SET MY OWN SIGNALSTATE TO START AS WELL.
      // THIS SPREADS THROUGHOUT THE CHAIN.

      // GET SIGNAL STATE HERE!!!!
      if(getSignalState(getLastValueReceivedOnFace(f)) == START)
      {
        signalState = START;

        if(getBlinkRole(getLastValueReceivedOnFace(f)) == KING)
        {
          foundKing = true;
        }
      }
    }

    if(signalState == START && foundKing)
    {
      Role = KNIGHT;
    }
    else
    {
      Role = WIZARD;
    }
  }
}

void startLoop()
{

  signalState = PLAY;
   // Look for neighbors who have not heard the START news
  FOREACH_FACE(f)
  {
    // IF WE DETECT A NEIGHBOR!
    if(!isValueReceivedOnFaceExpired(f))
    {
      // IF OUR NEIGHBOR'S FACE IS STILL SET TO SETUP, I.E. - It hasn't been set to START
      // LET'S STAY IN START MODE.
      if(getSignalState(getLastValueReceivedOnFace(f)) == SETUP)
      {
        signalState = START;
      }
    }
  }
}

void playLoop()
{
  //signalState = PLAY;

  FOREACH_FACE(f)
  {
    // IF WE HAVE A NEIGHBOR
    if(!isValueReceivedOnFaceExpired(f))
    {
      // If this neighbor isn't in PLAY, Stay in PLAY!
      
      // GET SIGNAL STATE  - PARSE WITH GET SIGNAL STATE
      if(getSignalState(getLastValueReceivedOnFace(f)) == SETUP)
      {
        signalState = SETUP;
      }
    }
  }
  
  if(buttonDoubleClicked())
  {
    switchTeams();
  }

  if(buttonLongPressed())
  {
    signalState = SETUP;
  }
}

void displayRole()
{
  switch(Role)
  {
    case PAWN:
      setColor(CYAN);
      break;

    case KING:
      switch(Team)
      {
        case WHITETEAM:
          setColor(WHITE);
          displayKing();
          break; 

        case BLACKTEAM:
          setColor(BLACKOUT);
          displayKing();
          break;
      }
      break;
        
    case KNIGHT:
      switch(Team)
      {
        case WHITETEAM:
          setColor(WHITE);
          displayKnight();
          break; 

        case BLACKTEAM:
          setColor(BLACKOUT);
          displayKnight();
          break;
      }
      break; 

    case WIZARD:
      switch(Team)
      {
        case WHITETEAM:
          setColor(WHITE);
          displayWizard();
          break; 

        case BLACKTEAM:
          setColor(BLACKOUT);
          displayWizard();
          break;
      }
      break;
  }
}


void displayKing()
{
  FOREACH_FACE(f) 
  {
    setColorOnFace(YELLOW, f);
    f+=1;
  }
}

void displayKnight()
{
  FOREACH_FACE(f) 
  {
    setColorOnFace(RED, f / 2);
  }
}

void displayWizard()
{
  FOREACH_FACE(f) 
  {
    setColorOnFace(BLUE, f);
    f+=2;
  }
}

void switchTeams()
{
  if(Team == WHITETEAM)
    {
      Team = BLACKTEAM;
    }
    else
    {
      Team = WHITETEAM;
    }
}


byte getSignalState(byte data)
{
  //returns bits E and F
  return (data & 3);
}

byte getBlinkRole(byte data) 
{
  //returns bits C and D
    return ((data >> 2) & 3);
}
