/**
 * @author Manuel Gachs Ballegeer
 */
package Deepspace;

import java.util.ArrayList;

/**
 * @brief Clase que controla la partida
 */
class GameUniverse {
    private final static int WIN = 10;
    
    private ArrayList<SpaceStation> spaceStations = new ArrayList<>();
    private SpaceStation currentStation;
    private EnemyStarShip currentEnemy;
    private GameStateController gameState;
    private Dice dice;
    private int currentSpaceStationIndex;
    private int turns;
    
    GameUniverse() {
        gameState = new GameStateController();
        dice = new Dice();
        turns = 0;
    }
    
    CombatResult combat(SpaceStation station,EnemyStarShip enemy) {
        throw new UnsupportedOperationException();
    }
    
    public CombatResult combat() {
        throw new UnsupportedOperationException();
    }
    
    public void discardHangar() {
        if (gameState.getState()==GameState.INIT || gameState.getState()==GameState.AFTERCOMBAT)
            currentStation.discardHangar();
    }
    
    public void discardShieldBooster(int i) {
        if (gameState.getState()==GameState.INIT || gameState.getState()==GameState.AFTERCOMBAT)
            currentStation.discardShieldBooster(i);
    }
    
    public void discardShieldBoosterInHangar(int i) {
        if (gameState.getState()==GameState.INIT || gameState.getState()==GameState.AFTERCOMBAT)
            currentStation.discardShieldBoosterInHangar(i);
    }
    
    public void discardWeapon(int i) {
        if (gameState.getState()==GameState.INIT || gameState.getState()==GameState.AFTERCOMBAT)
            currentStation.discardWeapon(i);
    }
    
    public void discardWeaponInHangar(int i) {
        if (gameState.getState()==GameState.INIT || gameState.getState()==GameState.AFTERCOMBAT)
            currentStation.discardWeaponInHangar(i);
    }
    
    public GameState getState() { return gameState.getState(); }
    
    GameUniverseToUI getUIversion() { return new GameUniverseToUI(currentStation,currentEnemy); }
    
    public boolean haveAWinner() { return currentStation.getNMedals()==WIN; }
    
    public void init(ArrayList<String> names) {
        throw new UnsupportedOperationException();
    }
    
    public void mountShieldBooster(int i) {
        if (gameState.getState()==GameState.INIT || gameState.getState()==GameState.AFTERCOMBAT)
            currentStation.mountShieldBooster(i);
    }
    
    public void mountWeapon(int i) {
        if (gameState.getState()==GameState.INIT || gameState.getState()==GameState.AFTERCOMBAT)
            currentStation.mountWeapon(i);
    }
    
    public boolean nextTurn() {
        throw new UnsupportedOperationException();
    }
    
    @Override
    public String toString() {
        String aux = "Estación espacial actual:\n"+currentStation.toString();
        aux += "\nEnemigo actual:\n"+currentEnemy.toString();
        return aux;
    }
}
