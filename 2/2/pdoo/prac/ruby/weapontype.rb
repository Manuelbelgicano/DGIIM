#encoding:utf-8
module Deepspace
  # Tipos de armas
  module WeaponType
    class Type
      attr_reader :power

      def initialize(power_val)
        @power = power_val
      end
   end

    LASER = Type.new(2.0)
    MISSILE = Type.new(3.0)
    PLASMA = Type.new(4.0)
  end
end
