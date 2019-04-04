/**
 * @author Manuel Gachs Ballegeer
 */
package Deepspace;

/**
 * @brief Potenciadores de escudo
 */
class ShieldBooster {
    private String name;
    private float boost;
    private int uses;
    
    ShieldBooster(String BoosterName,float BoostValue,int BoosterUses) {
        name = BoosterName;
        boost = BoostValue;
        uses = BoosterUses;
    }
    ShieldBooster(ShieldBooster s) {
        name = s.name;
        boost = s.boost;
        uses = s.uses;
    }
    public float getBoost() {return boost;}
    public int getUses() {return uses;}
    public float useIt() {
        if (uses>0) {
            uses = uses - 1;
            return boost;
        } else
            return 1.0f;
    }
}