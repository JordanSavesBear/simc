# Executed before combat begins. Accepts non-harmful actions only.
actions.precombat=flask
actions.precombat+=/food
actions.precombat+=/augmentation
# Snapshot raid buffed stats before combat begins and pre-potting is done.
actions.precombat+=/snapshot_stats
actions.precombat+=/retribution_aura
actions.precombat+=/arcane_torrent,if=talent.final_reckoning&talent.seraphim
actions.precombat+=/shield_of_vengeance
actions.precombat+=/variable,name=trinket_1_buffs,value=trinket.1.has_buff.strength|trinket.1.has_buff.mastery|trinket.1.has_buff.versatility|trinket.1.has_buff.haste|trinket.1.has_buff.crit
actions.precombat+=/variable,name=trinket_2_buffs,value=trinket.2.has_buff.strength|trinket.2.has_buff.mastery|trinket.2.has_buff.versatility|trinket.2.has_buff.haste|trinket.2.has_buff.crit
actions.precombat+=/variable,name=trinket_1_sync,op=setif,value=1,value_else=0.5,condition=variable.trinket_1_buffs&(trinket.1.cooldown.duration%%cooldown.crusade.duration=0|cooldown.crusade.duration%%trinket.1.cooldown.duration=0|trinket.1.cooldown.duration%%cooldown.avenging_wrath.duration=0|cooldown.avenging_wrath.duration%%trinket.1.cooldown.duration=0)
actions.precombat+=/variable,name=trinket_2_sync,op=setif,value=1,value_else=0.5,condition=variable.trinket_2_buffs&(trinket.2.cooldown.duration%%cooldown.crusade.duration=0|cooldown.crusade.duration%%trinket.2.cooldown.duration=0|trinket.2.cooldown.duration%%cooldown.avenging_wrath.duration=0|cooldown.avenging_wrath.duration%%trinket.2.cooldown.duration=0)
actions.precombat+=/variable,name=trinket_priority,op=setif,value=2,value_else=1,condition=!variable.trinket_1_buffs&variable.trinket_2_buffs|variable.trinket_2_buffs&((trinket.2.cooldown.duration%trinket.2.proc.any_dps.duration)*(1.5+trinket.2.has_buff.strength)*(variable.trinket_2_sync))>((trinket.1.cooldown.duration%trinket.1.proc.any_dps.duration)*(1.5+trinket.1.has_buff.strength)*(variable.trinket_1_sync))

# Executed every time the actor is available.
actions=auto_attack
actions+=/rebuke
actions+=/call_action_list,name=cooldowns
actions+=/call_action_list,name=es_fr_pooling,if=(!raid_event.adds.exists|raid_event.adds.up|raid_event.adds.in<9|raid_event.adds.in>30)&(talent.execution_sentence&cooldown.execution_sentence.remains<9&spell_targets.divine_storm<5|talent.final_reckoning&cooldown.final_reckoning.remains<9)&(!buff.crusade.up|buff.crusade.stack=10)&target.time_to_die>8
actions+=/call_action_list,name=es_fr_active,if=debuff.execution_sentence.up|debuff.final_reckoning.up
actions+=/call_action_list,name=generators

actions.cooldowns=potion,if=buff.avenging_wrath.up|buff.crusade.up&buff.crusade.stack=10|fight_remains<25
actions.cooldowns+=/lights_judgment,if=spell_targets.lights_judgment>=2|!raid_event.adds.exists|raid_event.adds.in>75|raid_event.adds.up
actions.cooldowns+=/fireblood,if=(buff.avenging_wrath.up|buff.crusade.up&buff.crusade.stack=10)&!talent.execution_sentence
actions.cooldowns+=/use_item,name=algethar_puzzle_box,if=(cooldown.avenging_wrath.remains<5&!talent.crusade|cooldown.crusade.remains<5&talent.crusade)&(holy_power>=5&time<5|holy_power>=3&time>5)
actions.cooldowns+=/use_item,slot=trinket1,if=(buff.avenging_wrath.up|buff.crusade.up&buff.crusade.stack=10)&(!trinket.2.has_cooldown|trinket.2.cooldown.remains|variable.trinket_priority=1)|trinket.1.proc.any_dps.duration>=fight_remains
actions.cooldowns+=/use_item,slot=trinket2,if=(buff.avenging_wrath.up|buff.crusade.up&buff.crusade.stack=10)&(!trinket.1.has_cooldown|trinket.1.cooldown.remains|variable.trinket_priority=2)|trinket.2.proc.any_dps.duration>=fight_remains
actions.cooldowns+=/use_item,slot=trinket1,if=!variable.trinket_1_buffs&(trinket.2.cooldown.remains|!variable.trinket_2_buffs|!buff.crusade.up&cooldown.crusade.remains>20|!buff.avenging_wrath.up&cooldown.avenging_wrath.remains>20)
actions.cooldowns+=/use_item,slot=trinket2,if=!variable.trinket_2_buffs&(trinket.1.cooldown.remains|!variable.trinket_1_buffs|!buff.crusade.up&cooldown.crusade.remains>20|!buff.avenging_wrath.up&cooldown.avenging_wrath.remains>20)
actions.cooldowns+=/shield_of_vengeance,if=(!talent.execution_sentence|cooldown.execution_sentence.remains<52)&fight_remains>15
actions.cooldowns+=/avenging_wrath,if=((holy_power>=4&time<5|holy_power>=3&time>5)|talent.holy_avenger&cooldown.holy_avenger.remains=0)&(!talent.seraphim|!talent.final_reckoning|cooldown.seraphim.remains>0)
actions.cooldowns+=/crusade,if=holy_power>=5&time<5|holy_power>=3&time>5
actions.cooldowns+=/holy_avenger,if=time_to_hpg=0&holy_power<=2&(buff.avenging_wrath.up|talent.crusade&(cooldown.crusade.remains=0|buff.crusade.up)|fight_remains<20)
actions.cooldowns+=/final_reckoning,if=(holy_power>=4&time<8|holy_power>=3&time>=8)&(cooldown.avenging_wrath.remains>gcd|cooldown.crusade.remains&(!buff.crusade.up|buff.crusade.stack>=10))&(time_to_hpg>0|holy_power=5)&(!talent.seraphim|buff.seraphim.up)&(!raid_event.adds.exists|raid_event.adds.up|raid_event.adds.in>40)&(!buff.avenging_wrath.up|holy_power=5|cooldown.hammer_of_wrath.remains)

actions.es_fr_active=fireblood
actions.es_fr_active+=/call_action_list,name=finishers,if=holy_power=5|debuff.judgment.up|debuff.final_reckoning.up&(debuff.final_reckoning.remains<gcd.max|spell_targets.divine_storm>=2&!talent.execution_sentence)|debuff.execution_sentence.up&debuff.execution_sentence.remains<gcd.max
actions.es_fr_active+=/divine_toll,if=holy_power<=2
actions.es_fr_active+=/wake_of_ashes,if=holy_power<=2&(debuff.final_reckoning.up&debuff.final_reckoning.remains<gcd*2&!talent.divine_resonance|debuff.execution_sentence.up&debuff.execution_sentence.remains<gcd|spell_targets.divine_storm>=5&talent.divine_resonance&talent.execution_sentence)
actions.es_fr_active+=/blade_of_justice,if=talent.expurgation&(!talent.divine_resonance&holy_power<=3|holy_power<=2)
actions.es_fr_active+=/judgment,if=!debuff.judgment.up&holy_power>=2
actions.es_fr_active+=/call_action_list,name=finishers
actions.es_fr_active+=/wake_of_ashes,if=holy_power<=2
actions.es_fr_active+=/blade_of_justice,if=holy_power<=3
actions.es_fr_active+=/judgment,if=!debuff.judgment.up
actions.es_fr_active+=/hammer_of_wrath
actions.es_fr_active+=/crusader_strike
actions.es_fr_active+=/arcane_torrent
actions.es_fr_active+=/exorcism
actions.es_fr_active+=/consecration

actions.es_fr_pooling=seraphim,if=holy_power=5&(!talent.final_reckoning|cooldown.final_reckoning.remains<=gcd*3)&(!talent.execution_sentence|cooldown.execution_sentence.remains<=gcd*3|talent.final_reckoning)
actions.es_fr_pooling+=/call_action_list,name=finishers,if=holy_power=5|debuff.final_reckoning.up|buff.crusade.up&buff.crusade.stack<10
actions.es_fr_pooling+=/hammer_of_wrath,if=talent.vanguards_momentum
actions.es_fr_pooling+=/wake_of_ashes,if=holy_power<=2&talent.ashes_to_dust&(cooldown.crusade.remains|cooldown.avenging_wrath.remains)
actions.es_fr_pooling+=/blade_of_justice,if=holy_power<=3
actions.es_fr_pooling+=/judgment,if=!debuff.judgment.up
actions.es_fr_pooling+=/hammer_of_wrath
actions.es_fr_pooling+=/crusader_strike,if=cooldown.crusader_strike.charges_fractional>=1.75&(holy_power<=2|holy_power<=3&cooldown.blade_of_justice.remains>gcd*2|holy_power=4&cooldown.blade_of_justice.remains>gcd*2&cooldown.judgment.remains>gcd*2)
actions.es_fr_pooling+=/seraphim,if=!talent.final_reckoning&cooldown.execution_sentence.remains<=gcd*3
actions.es_fr_pooling+=/call_action_list,name=finishers
actions.es_fr_pooling+=/crusader_strike
actions.es_fr_pooling+=/arcane_torrent,if=holy_power<=4
actions.es_fr_pooling+=/exorcism
actions.es_fr_pooling+=/seraphim,if=(!talent.final_reckoning|cooldown.final_reckoning.remains<=gcd*3)&(!talent.execution_sentence|cooldown.execution_sentence.remains<=gcd*3|talent.final_reckoning)
actions.es_fr_pooling+=/consecration

actions.finishers=variable,name=ds_castable,value=spell_targets.divine_storm>=2|buff.empyrean_power.up&!debuff.judgment.up&!buff.divine_purpose.up|buff.crusade.up&buff.crusade.stack<10&buff.empyrean_legacy.up&!talent.justicars_vengeance
actions.finishers+=/seraphim,if=(cooldown.avenging_wrath.remains>15|cooldown.crusade.remains>15)&!talent.final_reckoning&(!talent.execution_sentence|spell_targets.divine_storm>=5)&(!raid_event.adds.exists|raid_event.adds.in>40|raid_event.adds.in<gcd|raid_event.adds.up)|fight_remains<15&fight_remains>5|buff.crusade.up&buff.crusade.stack<10
actions.finishers+=/execution_sentence,if=(buff.crusade.down&cooldown.crusade.remains>10|buff.crusade.stack>=3|cooldown.avenging_wrath.remains>10)&(!talent.final_reckoning|cooldown.final_reckoning.remains>10)&target.time_to_die>8&(spell_targets.divine_storm<5|talent.executioners_wrath)
actions.finishers+=/radiant_decree,if=(buff.crusade.down&cooldown.crusade.remains>5|buff.crusade.stack>=3|cooldown.avenging_wrath.remains>5)&(!talent.final_reckoning|cooldown.final_reckoning.remains>5)
actions.finishers+=/divine_storm,if=variable.ds_castable&(!buff.empyrean_legacy.up|buff.crusade.up&buff.crusade.stack<10)&((!talent.crusade|cooldown.crusade.remains>gcd*3)&(!talent.execution_sentence|cooldown.execution_sentence.remains>gcd*6|cooldown.execution_sentence.remains>gcd*4&holy_power>=4|target.time_to_die<8|spell_targets.divine_storm>=5|!talent.seraphim&cooldown.execution_sentence.remains>gcd*2)&(!talent.final_reckoning|cooldown.final_reckoning.remains>gcd*6|cooldown.final_reckoning.remains>gcd*4&holy_power>=4|!talent.seraphim&cooldown.final_reckoning.remains>gcd*2)|talent.holy_avenger&cooldown.holy_avenger.remains<gcd*3|buff.holy_avenger.up|buff.crusade.up&buff.crusade.stack<10)
actions.finishers+=/justicars_vengeance,if=((!talent.crusade|cooldown.crusade.remains>gcd*3)&(!talent.execution_sentence|cooldown.execution_sentence.remains>gcd*6|cooldown.execution_sentence.remains>gcd*4&holy_power>=4|target.time_to_die<8|!talent.seraphim&cooldown.execution_sentence.remains>gcd*2)&(!talent.final_reckoning|cooldown.final_reckoning.remains>gcd*6|cooldown.final_reckoning.remains>gcd*4&holy_power>=4|!talent.seraphim&cooldown.final_reckoning.remains>gcd*2)|talent.holy_avenger&cooldown.holy_avenger.remains<gcd*3|buff.holy_avenger.up|buff.crusade.up&buff.crusade.stack<10)&!buff.empyrean_legacy.up
actions.finishers+=/templars_verdict,if=(!talent.crusade|cooldown.crusade.remains>gcd*3)&(!talent.execution_sentence|cooldown.execution_sentence.remains>gcd*6|cooldown.execution_sentence.remains>gcd*4&holy_power>=4|target.time_to_die<8|!talent.seraphim&cooldown.execution_sentence.remains>gcd*2)&(!talent.final_reckoning|cooldown.final_reckoning.remains>gcd*6|cooldown.final_reckoning.remains>gcd*4&holy_power>=4|!talent.seraphim&cooldown.final_reckoning.remains>gcd*2)|talent.holy_avenger&cooldown.holy_avenger.remains<gcd*3|buff.holy_avenger.up|buff.crusade.up&buff.crusade.stack<10

actions.generators=call_action_list,name=finishers,if=holy_power=5|(debuff.judgment.up|holy_power=4)&buff.divine_resonance.up|buff.holy_avenger.up
actions.generators+=/hammer_of_wrath,if=talent.zealots_paragon
actions.generators+=/wake_of_ashes,if=holy_power<=2&talent.ashes_to_dust&(cooldown.avenging_wrath.remains|cooldown.crusade.remains)
actions.generators+=/divine_toll,if=holy_power<=2&!debuff.judgment.up&(!talent.seraphim|buff.seraphim.up)&(!raid_event.adds.exists|raid_event.adds.in>30|raid_event.adds.up)&!talent.final_reckoning&(!talent.execution_sentence|fight_remains<8|spell_targets.divine_storm>=5)&(cooldown.avenging_wrath.remains>15|cooldown.crusade.remains>15|fight_remains<8)
actions.generators+=/judgment,if=!debuff.judgment.up&holy_power>=2
actions.generators+=/wake_of_ashes,if=(holy_power=0|holy_power<=2&cooldown.blade_of_justice.remains>gcd*2)&(!raid_event.adds.exists|raid_event.adds.in>20|raid_event.adds.up)&(!talent.seraphim|cooldown.seraphim.remains>5)&(!talent.execution_sentence|cooldown.execution_sentence.remains>15|target.time_to_die<8|spell_targets.divine_storm>=5)&(!talent.final_reckoning|cooldown.final_reckoning.remains>15|fight_remains<8)&(cooldown.avenging_wrath.remains|cooldown.crusade.remains)
actions.generators+=/call_action_list,name=finishers,if=holy_power>=3&buff.crusade.up&buff.crusade.stack<10
actions.generators+=/exorcism
actions.generators+=/judgment,if=!debuff.judgment.up
actions.generators+=/hammer_of_wrath
actions.generators+=/blade_of_justice,if=holy_power<=3
actions.generators+=/call_action_list,name=finishers,if=(target.health.pct<=20|buff.avenging_wrath.up|buff.crusade.up|buff.empyrean_power.up)
actions.generators+=/consecration,if=!consecration.up&spell_targets.divine_storm>=2
actions.generators+=/crusader_strike,if=cooldown.crusader_strike.charges_fractional>=1.75&(holy_power<=2|holy_power<=3&cooldown.blade_of_justice.remains>gcd*2|holy_power=4&cooldown.blade_of_justice.remains>gcd*2&cooldown.judgment.remains>gcd*2)
actions.generators+=/call_action_list,name=finishers
actions.generators+=/consecration,if=!consecration.up
actions.generators+=/crusader_strike
actions.generators+=/arcane_torrent
actions.generators+=/consecration
