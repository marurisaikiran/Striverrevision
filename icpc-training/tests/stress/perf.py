#!/usr/bin/env python3
"""Worst-case (maximum constraint) timing for the heavier solutions."""
import os, random, subprocess, time
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
B = os.path.join(ROOT, ".build"); R = random.Random(1)
def rnd(n, lo, hi): return " ".join(str(R.randint(lo, hi)) for _ in range(n))
cases = {
 "greedy_06_stick_lengths": f"200000\n{rnd(200000,1,10**9)}\n",
 "greedy_12_concert_tickets": f"200000 200000\n{rnd(200000,1,10**9)}\n{rnd(200000,1,10**9)}\n",
 "greedy_13_towers": f"200000\n{rnd(200000,1,10**9)}\n",
 "greedy_16_traffic_lights": "1000000000 200000\n" + " ".join(map(str, R.sample(range(1, 10**9), 200000))) + "\n",
 "greedy_17_room_allocation": "200000\n" + "".join(f"{a} {a+R.randint(0,10**5)}\n" for a in (R.randint(1,10**9-10**5) for _ in range(200000))),
 "greedy_18_factory_machines": f"200000 1000000000\n{rnd(200000,1,10**9)}\n",
 "greedy_25_cracker_shops": "1\n100000 100000\n" + "".join(f"5 {' '.join(map(str,R.sample(range(1,100001),5)))}\n" for _ in range(100000)),
 "greedy_26_jai_hanuman": "5\n" + "".join(f"100000\n{rnd(100000,1,500000)}\n" for _ in range(5)),
 "greedy_29_coins": "33333 33333 33334\n" + "".join(f"{rnd(3,1,10**9)}\n" for _ in range(100000)),
 "bitwise_03_gray_code": "16\n",
 "bitwise_07_orxor": f"20\n{rnd(20,0,2**30-1)}\n",
 "bitwise_08_jackpot": "1000\n" + "".join(f"{R.randint(2,10**9)}\n" for _ in range(1000)),
 "bitwise_11_the_67th_xor_problem": f"1\n3105\n{rnd(3105,0,10**9)}\n",
 "bitwise_13_xor_battle": "100\n" + "".join(f"200\n{rnd(200,1,10**18)}\n{''.join(R.choice('01') for _ in range(200))}\n" for _ in range(100)),
 "bitwise_14_xor_matching": "17 5\n",
 "number-theory_05_exponentiation_ii": "100000\n" + "".join(f"{rnd(3,0,10**9)}\n" for _ in range(100000)),
 "number-theory_06_counting_divisors": "100000\n" + "\n".join(str(R.randint(1,10**6)) for _ in range(100000)) + "\n",
 "number-theory_07_common_divisors": f"200000\n{rnd(200000,1,10**6)}\n",
 "number-theory_08_next_prime": "20\n" + "\n".join(str(10**12 - i * 37) for i in range(20)) + "\n",
 "number-theory_09_modulo_equality": f"1\n500000\n{rnd(500000,0,10**9)}\n{rnd(500000,10**8,10**9)}\n",
 "number-theory_10_obtain_desired_std_dev": "10\n" + "".join("99999 100000\n" for _ in range(10)),
 "number-theory_13_prime_multiples": "1000000000000000000 20\n2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71\n",
 "number-theory_14_sum_of_divisors": "1000000000000\n",
 "number-theory_15_divisor_analysis": "100000\n" + "".join(f"{p} 1000000000\n" for p in [x for x in range(2, 1300000) if all(x % q for q in range(2, int(x**.5)+1))][:100000]),
 "number-theory_17_maximum_gcd_on_whiteboard": f"1\n200000 5\n{rnd(200000,1,200000)}\n",
 "number-theory_18_substring_problem": "1\n1000000 1\n",
 "number-theory_19_steel_bar_durability": "".join(R.choice("0123456789") for _ in range(20000)) + "\n5\n" + "499 7\n" * 5,
 "number-theory_20_isro_digit_sum": "25\n" + "".join("10000\n" + "".join(f"{R.randint(1,10**14)} {R.randint(1 if i==0 else 0,9)}\n" for i in range(10000)) for _ in range(25)),
}
worst = 0
for name, inp in cases.items():
    t = time.time(); r = subprocess.run([os.path.join(B, name)], input=inp, capture_output=True, text=True); dt = time.time() - t
    worst = max(worst, dt)
    print(f"{name:45s} {dt:6.2f}s {'OK' if r.returncode == 0 else 'RC=' + str(r.returncode)}")
print(f"slowest: {worst:.2f}s")
