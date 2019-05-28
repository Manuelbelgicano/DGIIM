/**
 * @author Manuel Gachs Ballegeer
 */
package Deepspace;

/**
 * @brief Potenciadores de escudo
 */
class ShieldBooster implements Copyable <ShieldBooster>, CombatElement {
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
    @Override
    public int getUses() {return uses;}
    @Override
    public float useIt() {
        if (uses>0) {
            uses = uses - 1;
            return boost;
        } else
            return 1.0f;
    }
    
    ShieldToUI getUIversion() { return new ShieldToUI(this);  }
    
    @Override
    public String toString() {
        String aux = "Nombre: " + name;
        aux += ", Potencia: " + boost;
        aux += ", Usos: " + uses;
        return aux;
    }

    @Override
    public ShieldBooster copy() {
        return new ShieldBooster(this);
    }
}