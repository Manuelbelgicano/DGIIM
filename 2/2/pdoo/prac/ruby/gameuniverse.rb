#encoding:utf-8

require "./lib/GameUniverseToUI.rb"
require "./lib/GameStateController.rb"
require_relative "./dice.rb"
require_relative "./spacestation.rb"
require_relative "./enemystarship"
require_relative "./gamecharacter.rb"
require_relative "./combatresult.rb"

module Deepspace
  # Clase que desarrolla la partida
  class GameUniverse
    # Puntos necesarios para ganar
    @@WIN = 10
    
    attr_reader :gameState

    def initialize
      @gameState = GameStateController.new
      @turns = 0
      @dice = Dice.new
      @currentStation = nil
      @currentEnemy = nil
      @spaceStations = Array.new
    end

    # Implementación en la práctica 3
    def combatGo(station,enemy)
    end

    # Implementación en la práctica 3
    def combat
    end
    
    # La nave del turno descarta el hangar
    def discardHangar
      if @gameState.state==GameState::INIT or @gameState.state==GameState::AFTERCOMBAT
        @currentStation.discardHangar
      end
    end

    # La nave del turno descarta un potenciador de escudo
    def discardShieldBooster(i)
      if @gameState.state==GameState::INIT or @gameState.state==GameState::AFTERCOMBAT
        @currentStation.discardShieldBooster(i)
      end
    end

    # La nave del turno descarta un potenciador de escudo de su hangar
    def discardShieldBoosterInHangar(i)
      if @gameState.state==GameState::INIT or @gameState.state==GameState::AFTERCOMBAT
        @currentStation.discardShieldBoosterInHangar(i)
      end
    end

    # La nave del turno descarta un arma
    def discardWeapon(i)
      if @gameState.state==GameState::INIT or @gameState.state==GameState::AFTERCOMBAT
        @currentStation.discardWeapon(i)
      end
    end

    # La nave del turno descarta un arma de su hangar
    def discardWeaponInHangar(i)
      if @gameState.state==GameState::INIT or @gameState.state==GameState::AFTERCOMBAT
        @currentStation.discardWeaponInHangar(i)
      end
    end

    def getUIVersion
      GameUniverseToUI.new(self)
    end

    # Comprueba si la nave del turno ha ganado la partida
    def haveAWinner
      if @currentStation.nMedals>=@@WIN
        return true
      end
      return false
    end

    # Implementación en la práctica 3
    def init(names)
    end

    # Monta un escudo con índice 'i' en la nave
    def mountShieldBooster(i)
      if @gameState.state==GameState::INIT or @gameState.state==GameState::AFTERCOMBAT
        @currentStation.mountShieldBooster(i)
      end
    end

    # Monta un arma con índice 'i' en la nave
    def mountWeapon(i)
      if @gameState.state==GameState::INIT or @gameState.state==GameState::AFTERCOMBAT
        @currentStation.mountWeapon(i)
      end
    end

    # Implementación en la práctica 3
    def nextTurn
    end

    def to_s
      getUIVersion.to_s
    end
  end
end
