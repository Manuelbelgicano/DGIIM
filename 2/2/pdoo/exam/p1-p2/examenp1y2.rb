#encoding:utf-8

require "./shieldbooster.rb"
require "./damage.rb"
require "./figura.rb"

module ModuloExamen
	class ExamenP1y2
	
		def self.main
			puts "Creamos dos círculos y dos rectángulos:"
			puts "\tCírculos:\n\t\t1º => radio 1.0\n\t\t2º => radio 2.0"
			puts "\tRectángulos:\n\t\t1º => 2.0x2.0\n\t\t2º => 2.0x4.0"
			
			figuras = [Figura.newCircle(1.0),Figura.newCircle(2.0),Figura.newRectangle(2.0,2.0),Figura.newRectangle(3.0,4.0)]
			areas = 0.0
			
			figuras.each do |figura|
				areas += figura.area
			end
			area_media = areas/Figura.nFiguras
			puts "El área media de las figuras es: #{area_media}"
			
			puts "\nCreamos el daño:"
			weapons_damage = [Deepspace::WeaponType::LASER,Deepspace::WeaponType::MISSILE,Deepspace::WeaponType::MISSILE]
			damage = Deepspace::Damage.newSpecificWeapons(weapons_damage,1)
			puts damage.to_s
			puts "Lo ajustamos a las siguientes colecciones:"
			weapons_adjust = [Deepspace::Weapon.new("laser1",Deepspace::WeaponType::LASER,1),Deepspace::Weapon.new("laser2",Deepspace::WeaponType::LASER,1),Deepspace::Weapon.new("misil",Deepspace::WeaponType::MISSILE,1),Deepspace::Weapon.new("plasma",Deepspace::WeaponType::PLASMA,1)]
			shields_adjust = [Deepspace::ShieldBooster.new("uno",1,1),Deepspace::ShieldBooster.new("dos",1,1)]
			puts "Colección de armas:"
			weapons_adjust.each do |weapon|
				puts weapon.to_s + "\n"
			end
			puts "Colección de escudos:"
			shields_adjust.each do |shield|
				puts shield.to_s + "\n"
			end
			puts "El daño ajustado es el siguiente:"
			puts damage.adjust(weapons_adjust,shields_adjust)
		end
	end
end

ModuloExamen::ExamenP1y2.main
