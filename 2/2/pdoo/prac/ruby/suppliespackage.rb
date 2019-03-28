#encoding:utf-8
module Deepspace
  # Paquete de suministros
  class SuppliesPackage
    attr_reader :ammoPower, :fuelUnits, :shieldPower
    
    def initialize(ammo_p,fuel_u,shield_p)
      @ammoPower = ammo_p
      @fuelUnits = fuel_u
      @shieldPower = shield_p
    end
    
    def self.newCopy(supplies_package)
      new(supplies_package.ammoPower,supplies_package.fuelUnits,supplies_package.shieldPower)
    end
    def to_s
      "ammoPower = #{@ammoPower}\nfuelUnits = #{@fuelUnits}\nshieldPower = #{@shieldPower}"
    end
  end
end
