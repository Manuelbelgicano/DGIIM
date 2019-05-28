#encoding:utf-8

require_relative "damage"
require_relative "weapon"
require_relative "./lib/SpecificDamageToUI.rb"

module Deepspace

  class SpecificDamage<Damage

    public_class_method :new

    attr_reader :weapons
		
    def initialize(wl,s)
      super(s)
      @weapons = wl
    end
		
    def copy
      new SpecificDamage(@weapons,@nShields)
    end
		
    # Comprueba si el array 'w' contiene armas del tipo 't'
    private def arrayContainsType(w,t)
      w.each_index do |i|
        if w[i].type==t
          return i
        end
      end
      return -1
    end
    
    def adjust(w,s)
      new_shields = [@nShields,s.length].min
        new_weapons = Array.new(@weapons)

        new_weapons.each_with_index do |wt,i|
          if (arrayContainsType(w,wt)==-1)
            new_weapons[i] = nil
          else
            index = arrayContainsType(w,wt)
            w_aux = Array.new
            w.each_index do |i|
              if i>=index
                w_aux << w[i].type
              end
            end
            if (new_weapons.count(wt)>w_aux.count(wt))
              new_weapons[i] = nil
            end
          end
        end

        new_weapons = new_weapons.compact
        SpecificDamage.new(new_weapons,new_shields)
    end

    def discardWeapon(w)
      type = w.type
      index = -1
      @weapons.each_index do |i|
        if @weapons[i]==type
          index = i
        end
      end
      if index!=-1
        @weapons.delete_at(index)
      end
    end

    def hasNoEffect
      return (@weapons.length==0 and super)
    end

    def getUIversion
      SpecificDamageToUI.new(self)
    end
  end
end
