#encoding:utf-8

require_relative "./damage.rb"
require_relative "./hangar.rb"
require "./lib/SpaceStationToUI.rb"
require_relative "./loot.rb"
require_relative "./shieldbooster.rb"
require_relative "./shotresult.rb"
require_relative "./suppliespackage.rb"
require_relative "./weapon.rb"
require_relative "./lib/CardDealer.rb"
require_relative 'transformation'

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

    def newCopy(station)
      @name = station.name
      @ammoPower = station.ammoPower
      @fuelUnits = station.fuelUnits
      @shieldPower = station.shieldPower
      @nMedals = station.nMedals
      @weapons = station.weapons
      @shieldBoosters = station.shieldBoosters
      @pendingDamage = station.pendingDamage
      @hangar = station.hangar
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
    def cleanUpMountedItems
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

    # Elimina un escudo de la nave
    def discardShieldBooster(i)
      if i>=0 and i<@shieldBoosters.length
        if @pendingDamage!=nil
          @pendingDamage.discardShieldBooster
        end
        @shieldBoosters.delete_at(i)
      end
    end
    
    # Elimina un arma de la nave
    def discardWeapon(i)
      if i>=0 and i<@weapons.length
        if @pendingDamage!=nil
          w = @weapons[i]
          @pendingDamage.discardWeapon(w)
          cleanPendingDamage
        end
        @weapons.delete_at(i)
      end
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

    # Calcula la potencia del disparo
    def fire
      factor = 1.0
      @weapons.each do |weapon|
        factor = factor*weapon.useIt
      end
      @ammoPower*factor
    end

    # Devuelve la velocidad de la estación como fracción de combustible
    def getSpeed
      @fuelUnits/@@MAXFUEL
    end

    # Equipa el escudo de índice 'i' del hangar a la estación
    def mountShieldBooster(i)
      if @hangar!=nil and i>=0
        @shieldBoosters << @hangar.removeShieldBooster(i)
      end
    end

    # Equipa el arma de índice 'i' del hangar a la estación
    def mountWeapon(i)
      if @hangar!=nil and i>=0
        @weapons << @hangar.removeWeapon(i)
      end
    end

    # Movimiento de la estación
    def move
      if @fuelUnits>0
        @fuelUnits = [0,@fuelUnits - @fuelUnits*getSpeed].max
      end
    end
    
    # Calcula el poder de escudo de la nave
    def protection
      factor = 1.0
      @shieldBoosters.each do |shield|
        factor = factor*shield.useIt
      end
      factor*@shieldPower
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
    
    # Determina si la nave aguanta un disparo
    def recieveShot(shot)
      myProtection = protection
      if myProtection>=shot
        @shieldPower = [0.0,@shieldPower - shot*@@SHIELDLOSSPERUNITSHOT].max
        return ShotResult::RESIST
      else
        @shieldPower = 0.0
        return ShotResult::DONOTRESIST
      end
    end

    # La nave recibe suministros
    def recieveSupplies(s)
      @ammoPower += s.ammoPower
      @fuelUnits = [@@MAXFUEL,@fuelUnits+s.fuelUnits].min
      @shieldPower += s.shieldPower
    end

    # Recepción de un botín
    def setLoot(loot)
      dealer = CardDealer.instance

      h = loot.nHangars
      if h>0
        hangar = dealer.nextHangar
        recieveHangar(hangar)
      end

      elements = loot.nSupplies
      for i in 0...elements 
        sup = dealer.nextSuppliesPackage
        recieveSupplies(sup)
      end

      elements = loot.nWeapons
      for i in 0...elements
        weap = dealer.nextWeapon
        recieveWeapon(weap)
      end

      elements = loot.nShields
      for i in 0...elements
        sh = dealer.nextShieldBooster
        recieveShieldBooster(sh)
      end

      medals = loot.nMedals
      @nMedals += medals

      if loot.getEfficient==true
        return Transformation::GETEFFICIENT
      elsif loot.spaceCity==true
        return Transformation::SPACECITY
      else
        return Transformation::NOTRANSFORM
      end
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

    def getUIversion
      SpaceStationToUI.new(self)
    end

    def to_s
      getUIversion.to_s
    end
  end
end
