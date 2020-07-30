
enum Roles {PAWN, KING, KNIGHT, WIZARD, JESTER, ALCHEMIST, QUEEN};
byte Role = PAWN;
bool receivedRole = false;

enum Teams {WHITETEAM, BLACKTEAM};
byte Team = WHITETEAM;

byte health = 3;

enum gameState {SETUP, START, PLAY};
// Then a byte to hold the current state.
byte gameState = SETUP;

Timer resetTimer;

#define BLACKOUT makeColorHSB(0,0,0)

#define PURPLE makeColorRGB (64, 20, 109)
#define GOLD makeColorRGB(255,213,0)
#define PULSE_LENGTH 2000
Timer pulseTimer;


//some Knight values here
Timer knightTimer1;
Timer knightTimer2;
Timer knightTimer3;
#define KNIGHTTIME 250
#define KNIGHTRED 20

#define WIZARDBLUE makeColorHSB(160, 180, 255)
//some Wizard values over here
Timer wizardTimer;
#define WIZARDTIME 25
byte blueness = 0;
byte blueDirection = 1;

#define COLOR_LENGTH 500
Timer colorOneTimer;
Timer colorTwoTimer;
Timer colorThreeTimer;
enum jesterStates {COLOR1, COLOR2, COLOR3 };
byte jesterState = COLOR1;


//some Alchemist values here

#define ALCHEMISTGREEN (makeColorHSB(100, 255, 215))
Timer alchemistTimer;
#define ALCHEMISTTIME 150
byte bombFace = 1;
byte bombDirection = 1;

#define PURPLE makeColorRGB (64, 20, 109)
Timer sparkleTimer;
#define SPARKLE_DURATION 100
byte saturationOne;
byte saturationTwo;
byte saturationThree;

void switchTeams();

void setup()
{
  // put your setup code here, to run once:
  setValueSentOnAllFaces(Role);
  pulseTimer.set(PULSE_LENGTH);
  randomize();
  colorOneTimer.set(COLOR_LENGTH);
  alchemistTimer.set(ALCHEMISTTIME);
}

void loop()
{
  switch (gameState)
  {
    case SETUP:
      setupLoop();
      break;

    case PLAY:
      playLoop();
      break;
  }

  displayRole();
}

void setupLoop()
{
  if (!resetTimer.isExpired()) receivedRole = false;

  if (buttonSingleClicked())
  {
    if (Role == KING)
    {
      Role = PAWN;
    }
    else
    {
      Role = KING;
    }
  }

  if (buttonDoubleClicked() && Role == KING)
  {
    receivedRole = true;
  }

  // CHECK FOR START SIGNAL
  if (resetTimer.isExpired())
    FOREACH_FACE(f)
  {
    if (!receivedRole)
    {
      // IF WE DETECT A NEIGHBOR!
      if (!isValueReceivedOnFaceExpired(f))
      {
        // IF MY NEIGHBOR'S FACE IS SAYING START, SET MY OWN SIGNALSTATE TO START AS WELL.
        // THIS SPREADS THROUGHOUT THE CHAIN.

        if (getLastValueReceivedOnFace(f) != PAWN)
        {
          Role = getLastValueReceivedOnFace(f) + 1;
          receivedRole = true;
          break;
        }
      }
    }
  }

  if (receivedRole)
  {
    resetTimer.set(100);
    setValueSentOnAllFaces(Role);
    gameState = PLAY;
  }
}

void playLoop()
{
  if (buttonDoubleClicked())
  {
    switchTeams();
  }

  if (buttonLongPressed())
  {
    Reset();
    gameState = SETUP;
  }

  FOREACH_FACE(f)
  {
    if (!isValueReceivedOnFaceExpired(f))
    {
      byte val = getLastValueReceivedOnFace(f);
      switch (val)
      {
        case PAWN:
          if (resetTimer.isExpired())
          {
            gameState = SETUP;
            Reset();
          }
      }
    }
  }
}

void Reset()
{
  resetTimer.set(100);
  Role = PAWN;
  health = 3;
  setValueSentOnAllFaces(Role);
}

void switchTeams()
{
  if (Team == WHITETEAM)
  {
    Team = BLACKTEAM;
  }
  else
  {
    Team = WHITETEAM;
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  _______ _            _____  _           _               ______
  |__   __| |          |  __ \(_)         | |             |___  /
    | |  | |__   ___  | |  | |_ ___ _ __ | | __ _ _   _     / / ___  _ __   ___
    | |  | '_ \ / _ \ | |  | | / __| '_ \| |/ _` | | | |   / / / _ \| '_ \ / _ \
    | |  | | | |  __/ | |__| | \__ \ |_) | | (_| | |_| |  / /_| (_) | | | |  __/
    |_|  |_| |_|\___| |_____/|_|___/ .__/|_|\__,_|\__, | /_____\___/|_| |_|\___|
                                   | |             __/ |
                                   |_|            |___/
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void displayRole()
{
  switch (Role)
  {
    case PAWN:
      setColor(CYAN);
      break;

    case KING:
      switch (Team)
      {
        case WHITETEAM:
          displayKing();
          setColorOnFace(WHITE, 0);
          break;

        case BLACKTEAM:
          displayKing();
          setColorOnFace(BLACKOUT, 0);
          break;
      }
      break;

    case KNIGHT:
      switch (Team)
      {
        case WHITETEAM:
          displayKnight();
          setColorOnFace(WHITE, 0);
          break;

        case BLACKTEAM:
          displayKnight();
          setColorOnFace(BLACKOUT, 0);
          break;
      }
      break;

    case WIZARD:
      switch (Team)
      {
        case WHITETEAM:
          displayWizard();
          setColorOnFace(WHITE, 0);
          break;

        case BLACKTEAM:
          displayWizard();
          setColorOnFace(BLACKOUT, 0);
          break;
      }
      break;

    case JESTER:
      switch (Team)
      {
        case WHITETEAM:
          displayJester();
          setColorOnFace(WHITE, 0);
          break;

        case BLACKTEAM:
          displayJester();
          setColorOnFace(BLACKOUT, 0);
          break;
      }
      break;

    case ALCHEMIST:
      switch (Team)
      {
        case WHITETEAM:
          displayAlchemist();
          setColorOnFace(WHITE, 0);
          break;

        case BLACKTEAM:
          displayAlchemist();
          setColorOnFace(BLACKOUT, 0);
          break;
      }
      break;

    case QUEEN:
      switch (Team)
      {
        case WHITETEAM:
          displayQueen();
          setColorOnFace(WHITE, 0);
          break;

        case BLACKTEAM:
          displayQueen();
          setColorOnFace(BLACKOUT, 0);
          break;
      }
      break;
  }
}

void displayKing()
{
  if (buttonSingleClicked())
  {
    health = health - 1;
  }

  byte saturation = 0;
  byte dimness = 0;

  FOREACH_FACE(f)
  {
    if (health == 3)
    {
      setColorOnFace(YELLOW, f);
      f += 1;
    }

    if (health == 2)
    {
      setColorOnFace(YELLOW, f);
      f += 3;
    }

    if (health == 1)
    {
      setColorOnFace(YELLOW, f);
      f += 5;
    }


    if (!pulseTimer.isExpired()) {
      int timerProgress = pulseTimer.getRemaining();
      saturation = 255 - (map(timerProgress, 0, PULSE_LENGTH, 0, 255));

      dimness = sin8_C(saturation);

    } else if (pulseTimer.isExpired()) {
      saturation = 0;
      dimness = 0;

      pulseTimer.set(PULSE_LENGTH);
    }

    setFaceColor(2, dim(PURPLE, dimness));
    setFaceColor(4, dim(PURPLE, dimness));

    setColorOnFace(GOLD,1);
    setColorOnFace(GOLD,5);
    setColorOnFace(GOLD,3);
  }
}

void displayKnight()
{
  setColor(makeColorHSB(KNIGHTRED, 255, 70));

  byte brightness1 = 0;
  byte brightness2 = 0;
  byte brightness3 = 0;

  //the knight has 3 identical timers running at offset times for the 3 sections of the "step" cycle
  //when one timer expires, instead of resetting itself, it resets the NEXT timer

  if (!knightTimer1.isExpired()) {
    byte timerProgress = knightTimer1.getRemaining();
    brightness1 = map(timerProgress, 0, KNIGHTTIME, 200, 255);
  } else if (knightTimer1.isExpired()) {
    knightTimer2.set(KNIGHTTIME); //next timer, GO!
  }

  if (!knightTimer2.isExpired()) {
    byte timerProgress = knightTimer2.getRemaining();
    brightness2 = map(timerProgress, 0, KNIGHTTIME, 200, 255);
  } else if (knightTimer2.isExpired()) {
    knightTimer3.set(KNIGHTTIME); //next timer, GO!
  }

  if (!knightTimer3.isExpired()) {
    byte timerProgress = knightTimer3.getRemaining();
    brightness3 = map(timerProgress, 0, KNIGHTTIME, 200, 255);
  } else if (knightTimer3.isExpired()) {
    knightTimer1.set(KNIGHTTIME); //next timer, GO! (cycling back to the top)
  }

  //now we can paint all the faces to flash on and off with the appropriate timers
  setColorOnFace(makeColorHSB(KNIGHTRED, 255, brightness3), 1);
  setColorOnFace(makeColorHSB(KNIGHTRED, 255, brightness3), 5);
  setColorOnFace(makeColorHSB(KNIGHTRED, 255, brightness2), 2);
  setColorOnFace(makeColorHSB(KNIGHTRED, 255, brightness2), 4);
  setColorOnFace(makeColorHSB(KNIGHTRED, 255, brightness1), 3);
}



void displayWizard()
{
  //faces 1 and 5 are static so let's just set those up
  setColorOnFace(dim(WIZARDBLUE, 110), 1);
  setColorOnFace(dim(WIZARDBLUE, 110), 5);

  //the flashy wizard pattern, I copied this structure from the alchemist code but tweaked the variables being affected


  if (!wizardTimer.isExpired()) {
    setColorOnFace(makeColorHSB(160, blueness, 255), 4);
    setColorOnFace(makeColorHSB(160, blueness, 255), 2);
    setColorOnFace(makeColorHSB(160, (255 - blueness), 255), 3);
  } else if (wizardTimer.isExpired()) {

    blueness = blueness + (8 * blueDirection);

    if (blueness > 245) {
      blueDirection = -1;
    }
    if (blueness < 10) {
      blueDirection = 1;
    }

    wizardTimer.set(WIZARDTIME);
  }
}


void displayJester()
{
  setColor(ORANGE);
/*  switch (jesterState) {

    case COLOR1:
      colorOne();
      break;

    case COLOR2 :
      colorTwo();
      break;

    case COLOR3:
      colorThree();

      break;
  }
  displaySignalState();
*/}

void colorOne() {


  jesterState = COLOR1;

  if (colorOneTimer.isExpired()) {
    jesterState = COLOR2;
    colorTwo();

  }
  colorTwoTimer.set(COLOR_LENGTH);
}

void colorTwo() {
  jesterState = COLOR2;

  if (colorTwoTimer.isExpired()) {
    jesterState = COLOR3;
    colorThree();
  }
  colorThreeTimer.set(COLOR_LENGTH);

}

void colorThree() {
  jesterState = COLOR3;

  if (colorThreeTimer.isExpired()) {
    jesterState = COLOR1;
    colorOne();


  }
  colorOneTimer.set(COLOR_LENGTH);

}

void displaySignalState() {
  switch (jesterState) {
    case COLOR1:
      colorOne();
      setColorOnFace(CYAN, 1);
      setColorOnFace(YELLOW, 2);
      setColorOnFace(MAGENTA, 4);
      setColorOnFace(ORANGE, 5);
      setColorOnFace(GREEN, 3);
      break;

    case COLOR2:
      colorTwo();

      setColorOnFace(GREEN, 1);
      setColorOnFace(CYAN, 2);
      setColorOnFace(YELLOW, 4);
      setColorOnFace(MAGENTA, 5);
      setColorOnFace(ORANGE, 3);
      break;

    case COLOR3:
      colorThree();
      setColorOnFace(ORANGE, 1);
      setColorOnFace(GREEN, 2);
      setColorOnFace(CYAN, 4);
      setColorOnFace(YELLOW, 5);
      setColorOnFace(MAGENTA, 3);
      break;


  }
}


void displayAlchemist()
{
  //now the actual animation code

  //first, let's just paint the whole thing a fun shade of green

  setColorOnFace(dim(ALCHEMISTGREEN, 140), 1);
  setColorOnFace(dim(ALCHEMISTGREEN, 140), 5);
  setColorOnFace(dim(ALCHEMISTGREEN, 210), 2);
  setColorOnFace(dim(ALCHEMISTGREEN, 210), 4);
  setColorOnFace(dim(ALCHEMISTGREEN, 255), 3);

  //^there's probably a more elegant way to do this, and I'd love to learn how!

  //okay, now we're going to have a timer that counts how long the bomb sits on each face

  if (!alchemistTimer.isExpired()) {
    //if the timer is NOT expired, paint the stated face like a bomb
    setColorOnFace(MAGENTA, bombFace);

  } else if (alchemistTimer.isExpired()) {
    //but if the timer IS expired, then change the bombFace by one in the direction the bomb is currently cycling

    bombFace = bombFace + (1 * bombDirection);

    if (bombFace == 5) {
      //when we hit Face 5, send the bomb back to the left
      bombDirection = -1;
    }

    if (bombFace == 1) {
      //when we hit Face 1, send the bomb back to the right
      bombDirection = 1;
    }

    //whenever the timer expires, reset it
    alchemistTimer.set(ALCHEMISTTIME);
  }
}

void displayQueen()
{
  setColorOnFace(PURPLE, 1);
  setColorOnFace(PURPLE, 5);

  if (sparkleTimer.isExpired()) {
    saturationOne = random(60) + 150;
    saturationTwo = random(50) + 120;
    saturationThree = random(40) + 180;


    sparkleTimer.set(SPARKLE_DURATION);
  }

  setColorOnFace(dim(WHITE, saturationOne), 2);
  setColorOnFace(dim(WHITE, saturationTwo), 4);
  setColorOnFace(dim(WHITE, saturationThree), 3);
}
