#encoding:utf-8

require "./lib/HangarToUI.rb"
require_relative "./weapon.rb"
require_relative "./shieldbooster.rb"

module Deepspace
  # Hangar
  class Hangar

    attr_reader :maxElements, :weapons, :shieldBoosters
    
    def initialize(capacity)
      @maxElements = capacity
      @weapons = Array.new()
      @shieldBoosters = Array.new()
    end

    # Constructor por copia
    def self.newCopy(h)
      n_hangar = Hangar.new(h.maxElements)
      h.weapons.each do |weapon|
        n_hangar.addWeapon(weapon)
      end
      h.shieldBoosters.each do |shield|
        n_hangar.addShieldBooster(shield)
      end
      return n_hangar
    end

    def getUIversion
      HangarToUI.new(self)
    end

    def to_s
      getUIversion.to_s
    end

    # Comprueba si hay espacio disponible
    private def spaceAvailable
      if (@weapons.length+@shieldBoosters.length)<@maxElements
        return true
      else
        return false
      end
    end

    # Añade un arma
    def addWeapon(w)
      if spaceAvailable
        @weapons << w
        return true
      end
      return false
    end

    # Añade un potenciador de escudo
    def addShieldBooster(s)
      if spaceAvailable
        @shieldBoosters << s
        return true
      end
      return false
    end

    # Devuelve el arma de índice 'w' y la elimina del hangar
    def removeWeapon(w)
        ret = Weapon.newCopy(@weapons[w])
        @weapons.delete_at(w)
      return ret
     end
    
    # Devuelve el potenciador de escudo de índice 's' y lo elimina del hangar
    def removeShieldBooster(s)
        ret = ShieldBooster.newCopy(@shieldBoosters[s])
        @shieldBoosters.delete_at(s)
      return ret
    end
  end
end
