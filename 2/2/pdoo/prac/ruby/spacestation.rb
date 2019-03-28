#encoding:utf-8

require_relative "./damage.rb"
require_relative "./hangar.rb"
require "./lib/SpaceStationToUI.rb"
require_relative "./loot.rb"
require_relative "./shieldbooster.rb"
require_relative "./suppliespackage.rb"
require_relative "./weapon.rb"

module Deepspace
  # Estación espacial
  class SpaceStation
    # Cantidad máxima de combustible de una estación espacial
    @@MAXFUEL = 100
    # Potencia de escudo perdido por cada unidad de potencia de disparo
    @@SHIELDLOSSPERUNITSHOT = 0.1
    
    attr_reader :name, :ammoPower, :fuelUnits, :shieldPower, :nMedals, :weapons, :shieldBoosters, :pendingDamage, :hangar

    def initialize(n,supplies)
      @name = n
      @ammoPower = supplies.ammoPower
      @fuelUnits = [@@MAXFUEL,supplies.fuelUnits].min
      @shieldPower = supplies.shieldPower
      @nMedals = 0
      @weapons = Array.new
      @shieldBoosters = Array.new
      @pendingDamage = nil
      @hangar = nil
    end

    # Asigna un nuevo valor de combustible
    private def assignFuelValue(f)
      if f<@@MAXFUEL
        @fuelUnits = f
      end
    end
    
    # Elimina el daño si no tiene efecto
    private def cleanPendingDamage()
      if @pendingDamage.hasNoEffect
        @pendingDamage = nil
      end
    end

    # Elimina las armas y potenciadores de escudos con 0 usos
    def cleanUpMountedUnits()
      @weapons.each_with_index do |weapon,i|
        if weapon.uses==0
          @weapons.delete_at(i)
        end
      end
      @shieldBoosters.each_with_index do |shield,i|
        if shield.uses==0
          @shieldBoosters.delete_at(i)
        end
      end
    end
  
    # Elimina el hangar
    def discardHangar
      @hangar = nil
    end

    # Implementación en la práctica 3
    def discardShieldBooster(i)
    end
    
    # Implementación en la práctica 3
    def discardWeapon(i)
    end

    # Elimina el potenciador de escudo con índice 'i' del hangar
    def discardShieldBoosterInHangar(i)
      if @hangar!=nil
        @hangar.removeShieldBooster(i)
      end
    end

    # Elimina el arma con índice 'i' del hangar
    def discardWeaponInHangar(i)
      if @hangar!=nil
        @hangar.removeWeapon(i)
      end
    end

    # Implementación en la práctica 3
    def fire
    end

    # Devuelve la velocidad de la estación como fracción de combustible
    def getSpeed
      @fuelUnits/@@MAXFUEL
    end

    # Equipa el escudo de índice 'i' del hangar a la estación
    def mountShieldBooster(i)
      if @hangar!=nil
        @shieldBoosters << @hangar.removeShieldBooster(i)
      end
    end

    # Equipa el arma de índice 'i' del hangar a la estación
    def mountWeapon(i)
      if @hangar!=nil
        @weapons << @hangar.removeWeapon(i)
      end
    end

    # Movimiento de la estación
    def move
      if @fuelUnits>0
        @fuelUnits = [0,@fuelUnits - @fuelUnits*getSpeed].max
      end
    end
    
    # Implementación en la práctica 3
    def protection
    end

    # Recibe un hangar
    def recieveHangar(h)
      if @hangar==nil
        @hangar = h
      end
    end

    # Añade un escudo al hangar en caso de ser posible
    def recieveShieldBooster(s)
      if @hangar!=nil
        @hangar.addShieldBooster(s)
      else
        return false
      end
    end

    # Añade un arma al hangar en caso de ser posible
    def recieveWeapon(w)
      if @hangar!=nil
        @hangar.addWeapon(w)
      else
        return false
      end
    end
    
    # Implementación en la práctica 3
    def recieveShot(shot)
    end

    # La nave recibe suministros
    def recieveSupplies(s)
      @ammoPower += s.ammoPower
      @fuelUnits = [@@MAXFUEL,@fuelUnits+s.fuelUnits].min
      @shieldPower += s.shieldPower
    end

    # Implementación en la práctica 3
    def setLoot(loot)
    end

    # Ajusta el  daño a la nave y lo guarda
    def setPendingDamage(d)
      @pendingDamage = d.adjust(@weapons,@shieldBoosters)
    end

    # Comprueba si el estado de la nave es válido
    def validState
      if @pendingDamage==nil or @pendingDamage.hasNoEffect
        return true
      else
        return false
      end
    end

    def getUIVersion
      SpaceStationToUI.new(self)
    end

    def to_s
      getUIVersion.to_s
    end
  end
end
