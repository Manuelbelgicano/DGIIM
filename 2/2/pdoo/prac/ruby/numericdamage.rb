#encoding:utf-8

require_relative "damage"
require_relative "./lib/NumericDamageToUI.rb"

module Deepspace
	
  class NumericDamage<Damage
    
    public_class_method :new

    attr_reader :nWeapons
		
		def initialize(w,s)
			super(s)
			@nWeapons = w
		end
		
		def copy
			new NumericDamage(@nWeapons,@nShields)
		end
		
    def adjust(w,s)
      new_shields = [@nShields,s.length].min
      new_weapons = [@nWeapons,w.length].min
      NumericDamage.new(new_weapons,new_shields)
    end
		
    def discardWeapon(w)
    	if @nWeapons>0
    		@nWeapons -= 1
    	end
    end
    
    def hasNoEffect
    	return (@nWeapons==0 and super)
    end

    def getUIversion
      NumericDamageToUI.new(self)
    end
  end
end
