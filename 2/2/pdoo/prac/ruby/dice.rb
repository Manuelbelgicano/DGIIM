#encoding:utf-8

require_relative "./gamecharacter.rb"

module Deepspace
  # Clase dado
  class Dice
    def initialize
      @NHANGARSPROB = 0.25
      @NSHIELDSPROB = 0.25 
      @NWEAPONSPROB = 0.33
      @FIRSTSHOTPROB = 0.25
      @EXTRAEFFICIENCYPROB = 0.8
      @GENERATOR = Random.new()
    end

    def initWithNHangars
      prob = @GENERATOR.rand(1.0)
      if prob<@NHANGARSPROB
        return 0
      else
        return 1
      end
    end

    def initWithNWeapons
      prob = @GENERATOR.rand(1.0)
      if prob<@NWEAPONSPROB
        return 1
      elsif @NWEAPONSPROB<=prob and prob<2*@NWEAPONSPROB
        return 2
      else
        return 3
      end
    end
    
    def initWithNShields
      prob = @GENERATOR.rand(1.0)
      if prob<@NSHIELDSPROB
        return 0
      else
        return 1
      end
    end

    def whoStarts(n)
      @GENERATOR.rand(n-1)
    end

    def firstShot
      prob = @GENERATOR.rand(1.0)
      if prob<@FIRSTSHOTPROB
        return GameCharacter::SPACESTATION
      else
        return GameCharacter::ENEMYSTARSHIP
      end
    end

    def spaceStationMoves(speed)
      prob = @GENERATOR.rand(1.0)
      if prob<speed
        return true
      else
        return false
      end
    end

    def extraEfficiency
      prob = @GENERATOR.rand(1.0)
      if prob<@EXTRAEFFICIENCYPROB
        return true
      else
        return false
      end
    end
  end
end
