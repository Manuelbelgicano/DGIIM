/**
 * @author Manuel Gachs Ballegeer
 */
package Deepspace;

import java.util.ArrayList;

/**
 * @brief Clase que controla la partida
 */
public class GameUniverse {
    private final static int WIN = 10;
    
    private ArrayList<SpaceStation> spaceStations = new ArrayList<>();
    private SpaceStation currentStation;
    private EnemyStarShip currentEnemy;
    private GameStateController gameState;
    private Dice dice;
    private int currentStationIndex;
    private int turns;
    private boolean hasSpaceCity;
    
    public GameUniverse() {
        gameState = new GameStateController();
        dice = new Dice();
        turns = 0;
        hasSpaceCity = false;
    }
    
    CombatResult combat(SpaceStation station,EnemyStarShip enemy) {
        GameCharacter ch = dice.firstShot();
        boolean enemy_wins;
        float fire;
        ShotResult result; 
        
        if (ch==GameCharacter.ENEMYSTARSHIP) {
            fire = enemy.fire();
            result = station.recieveShot(fire);
            
            if (result==ShotResult.RESIST) {
                fire = station.fire();
                result = enemy.recieveShot(fire);
                enemy_wins = (result==ShotResult.RESIST);
            } else {
                enemy_wins = true;
            }
        } else {
            fire = station.fire();
            result = enemy.recieveShot(fire);
            enemy_wins = (result==ShotResult.RESIST);
        }
               
        if (enemy_wins) {
            float s = station.getSpeed();
            boolean moves = dice.spaceStationMoves(s);
            if (!moves) {
                Damage damage = enemy.getDamage();
                station.setPendingDamage(damage);
                return CombatResult.ENEMYWINS;
            } else {
                station.move();
                return CombatResult.STATIONESCAPES;
            }
        } else {
            Loot aLoot = enemy.getLoot();
            Transformation transformation = station.setLoot(aLoot);
            if (transformation==Transformation.GETEFFICIENT) {
                makeStationEfficient();
                return CombatResult.STATIONWINSANDCONVERTS;
            } else if (transformation==Transformation.SPACECITY) {
                createSpaceCity();
                return CombatResult.STATIONWINSANDCONVERTS;
            } else
            return CombatResult.STATIONWINS;
        }
    }
    
    public CombatResult combat() {
        GameState state = gameState.getState();
        CombatResult combat_result;
        
        if (state==GameState.BEFORECOMBAT || state==GameState.INIT) {
            combat_result = combat(currentStation,currentEnemy);
            gameState.next(turns,spaceStations.size());
        } else
            combat_result = CombatResult.NOCOMBAT;
        return combat_result;
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
    
    public GameUniverseToUI getUIversion() { return new GameUniverseToUI(currentStation,currentEnemy); }
    
    public boolean haveAWinner() { return currentStation.getNMedals()==WIN; }
    
    public void init(ArrayList<String> names) {
        GameState state = gameState.getState();
        
        if (state==GameState.CANNOTPLAY) {
            CardDealer dealer = CardDealer.getInstance();
            
            for (String name: names) {
                SuppliesPackage supplies = dealer.nextSuppliesPackage();
                SpaceStation station = new SpaceStation(name,supplies);
                spaceStations.add(station);
                
                int nh = dice.initWithNHangars();
                int nw = dice.initWithNWeapons();
                int ns = dice.initWithNShields();
                Loot lo = new Loot(0,nw,ns,nh,0);
                station.setLoot(lo);
            }
            
            currentStationIndex = dice.whoStarts(spaceStations.size());
            currentStation = spaceStations.get(currentStationIndex);
            currentEnemy = dealer.nextEnemy();
            gameState.next(turns, spaceStations.size());
        }
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
        GameState state = gameState.getState();
        
        if (state==GameState.AFTERCOMBAT) {
            boolean stationState = currentStation.validState();
            if (stationState) {
                currentStationIndex = (currentStationIndex+1) % spaceStations.size();
                turns += 1;
                currentStation = spaceStations.get(currentStationIndex);
                currentStation.cleanUpMountedUnits();
                CardDealer dealer = CardDealer.getInstance();
                currentEnemy = dealer.nextEnemy();
                gameState.next(turns, spaceStations.size());
                return true;
            }
            return false;
        }
        return false;
    }
    
    @Override
    public String toString() {
        String aux = "Estación espacial actual:\n"+currentStation.toString();
        aux += "\nEnemigo actual:\n"+currentEnemy.toString();
        return aux;
    }
    
    public void createSpaceCity() {
        if (!hasSpaceCity) {
            ArrayList<SpaceStation> collaborators = new ArrayList<>();
            for (SpaceStation s: spaceStations)
                if (s!=currentStation)
                    collaborators.add(s);
            currentStation = new SpaceCity(currentStation,collaborators);
            hasSpaceCity = true;
        }
    }
    
    public void makeStationEfficient() {
        if (dice.extraEfficiency())
            currentStation = new BetaPowerEfficientSpaceStation(currentStation);
        else
            currentStation = new PowerEfficientSpaceStation(currentStation);
    }
}
