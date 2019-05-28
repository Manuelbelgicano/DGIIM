/**
 *  @author Manuel Gachs Ballegeer
 */
package Deepspace;

/**
 *  @brief Botín al vencer a una nave enemiga
 */
class Loot {
    private int nSupplies;
    private int nWeapons;
    private int nShields;
    private int nHangars;
    private int nMedals;
    private boolean getEfficient = false;
    private boolean spaceCity = false;
    
    Loot(int suppliesNumber,int weaponsNumber,int shieldsNumber,int hangarsNumber,int medalsNumber,boolean ef,boolean city) {
        nSupplies = suppliesNumber;
        nWeapons = weaponsNumber;
        nShields = shieldsNumber;
        nHangars = hangarsNumber;
        nMedals = medalsNumber;
        getEfficient = ef;
        spaceCity = city;
    }
    
    Loot(int suppliesNumber,int weaponsNumber,int shieldsNumber,int hangarsNumber,int medalsNumber) {
        nSupplies = suppliesNumber;
        nWeapons = weaponsNumber;
        nShields = shieldsNumber;
        nHangars = hangarsNumber;
        nMedals = medalsNumber;
    }
    
    public int getNSupplies() {return nSupplies;}
    public int getNWeapons() {return nWeapons;}
    public int getNShields() {return nShields;}
    public int getNHangars() {return nHangars;}
    public int getNMedals() {return nMedals;}
    public boolean getEfficient() { return getEfficient; }
    public boolean spaceCity() { return spaceCity; }
    
    LootToUI getUIversion() { return new LootToUI(this); }
    
    @Override
    public String toString() {
        String aux = "Suministros: " + nSupplies;
        aux += ", Armas: " + nWeapons;
        aux += ", Escudos: " + nShields;
        aux += ", Hangares: " + nHangars;
        aux += ", Medallas: " + nMedals + "\n";
        return aux;
    }
}
