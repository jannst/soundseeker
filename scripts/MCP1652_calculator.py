# Datasheet: https://www.mouser.de/datasheet/2/268/21876a-70653.pdf

# Run: 
#   python3 -i MCP1652_calculator.py
#
# >>> mcp1652_calc(Vin=5, Vout=75, Iout=20*10**-3, inductance=2.2*10**-6)
# duty cycle: 0.56
# switching freq: 750000
# Ton (time on): 7.466666666666668e-07
# Efficiency (%): 0.8
# Power out (Watt): 1.5
# Power in (Watt): 1.875
# Ipk (peak current inductor): 1.696969696969697
# Energy (per switching cycle in joules): 3.167676767676768e-06
# Inductor Input Power (Watt): 2.375757575757576
# Great. Inductor input power bigger than power In

def mcp1652_calc(Vin, Vout, Iout, inductance):
    if Vin < 3.8:
        print("voltage must be >= 3.8V")
        return

    duty_cycle = 0.56
    print("duty cycle: {0}".format(duty_cycle))

    sw_freq = 750 * 10**3
    print("switching freq: {0}".format(sw_freq))
    
    ton = (1/sw_freq)* duty_cycle
    print("Ton (time on): {0}".format(ton))

    efficiency = 0.8
    print("Efficiency (%): {0}".format(efficiency))

    power_out = Vout * Iout
    print("Power out (Watt): {0}".format(power_out))

    power_in = power_out / efficiency
    print("Power in (Watt): {0}".format(power_in))

    ipk = (Vin/inductance)*ton
    print("Ipk (peak current inductor): {0}".format(ipk))

    energy = (1/2)*inductance*ipk**2
    print("Energy (per switching cycle in joules): {0}".format(energy))

    inductor_input_power = energy * sw_freq
    print("Inductor Input Power (Watt): {0}".format(inductor_input_power))


    if inductor_input_power > power_in:
        print("Great. Inductor input power bigger than power In")
    else:
        print("Inductor input power not bigger than max input power. Will not work! Reduce inductor size!")











