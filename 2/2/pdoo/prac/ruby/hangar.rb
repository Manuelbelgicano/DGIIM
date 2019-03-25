#encoding:utf-8

require_relative "./lib/HangarToUI.rb"

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
      for i in 0..(h.weapons.length-1)
        n_hangar.addWeapon(h.weapons[i])
      end
      for i in 0..(h.shieldBoosters.length-1)
        n_hangar.addShieldBooster(h.shieldBoosters[i])
      end
    end

    def getUIVersion
      HangarToUI.new(self)
    end

    def to_s
      "maxElements = #{@maxElements}\n
      weapons = #{@weapons}\n
      shieldBoosters = #{@shieldBoosters}"
    end

    private def spaceAvailable
      if (@weapons.lenght+@shieldBoosters.length)<@maxElements
        return true
      else
        return false
      end
    end

    def addWeapon(w)
      if spaceAvailable
        @weapons << w
      end
    end

    def addShieldBooster(s)
      if spaceAvailable
        @shieldBoosters << s
      end
    end

    def removeWeapon(w)
      ret = @weapons[w]
      @weapons.delete_at(w)
      return ret
    end
    
    def removeShieldBooster(s)
      ret = @shieldBoosters[s]
      @shieldBoosters.delete_at(s)
      return ret
    end
  end
end
