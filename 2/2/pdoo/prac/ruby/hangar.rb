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
      # Arrays???
    end

    def getUIVersion
      HangarToUI.new(self)
    end

    def to_s
      "maxElements = #{@maxElements}\n
      weapons = #{@weapons}\n
      shieldBoosters = #{@shieldBoosters}"# Se hace así la salida de un array???
    end

    def spaceAvailable
    end

    def addWeapon(w)
    end

    def addShieldBooster(s)
    end

    def removeWeapon(w)
    end
    
    def removeShieldBooster(s)
    end

  end
end
