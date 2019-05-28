/**
 * @author Manuel Gachs Ballegeer
 */
package Deepspace;

import java.util.Random;

/**
 * @brief Dado del juego
 */
class Dice {
    private final float NHANGARSPROB;
    private final float NSHIELDSPROB;
    private final float NWEAPONSPROB;
    private final float FIRSTSHOTPROB;
    private final float EXTRAEFFICIENCYPROB;
    private final Random generator;
    
    Dice() {
        NHANGARSPROB = 0.25f;
        NSHIELDSPROB = 0.25f;
        NWEAPONSPROB = 0.33f;
        FIRSTSHOTPROB = 0.5f;
        EXTRAEFFICIENCYPROB = 0.8f;
        generator = new Random();
    }
    public int initWithNHangars() {
        float prob = generator.nextFloat();
        
        if (prob<NHANGARSPROB)
            return 0;
        else
            return 1;
    }
    public int initWithNWeapons() {
        float prob = generator.nextFloat();
        
        if (prob<NWEAPONSPROB)
            return 1;
        else if (NWEAPONSPROB<=prob && prob<2*NWEAPONSPROB)
            return 3;
        else
            return 2;
    }
    public int initWithNShields() {
        float prob = generator.nextFloat();
        
        if (prob<NSHIELDSPROB)
            return 0;
        else
            return 1;
    }
    public int whoStarts(int nPlayers) {
        return generator.nextInt(nPlayers-1);
    }
    public GameCharacter firstShot() {
        float prob = generator.nextFloat();
        
        if (prob<FIRSTSHOTPROB)
            return GameCharacter.SPACESTATION;
        else
            return GameCharacter.ENEMYSTARSHIP;
    }
    public boolean spaceStationMoves(float speed) {
        float prob = generator.nextFloat();
        
        return prob<speed;
    }
    
    public boolean extraEfficiency() {
        float prob = generator.nextFloat();
        
        if (prob<EXTRAEFFICIENCYPROB)
            return true;
        else
            return false;
    }
}