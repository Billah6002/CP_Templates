// P(x) = a0 + a1x + a2x^2 + ... + anx^n
// y[i] = P(i)
const int mod = 1e9 + 7;
ll BigMod(ll a, ll b) {
   ll res = 1;
   while (b) {
      if (b & 1) res = 1ll * res * a % mod;
      a = 1ll * a * a % mod;
      b >>= 1;
   }
   return res;
}
ll inv(ll x) {
   if (x < 0) x += mod;
   return BigMod(x, mod - 2);
}
ll add(ll &a, ll b) {
   a += b;
   if (a >= mod) a -= mod;
   return a;
}
ll eval (vector<ll> y, ll k) {
   int n = y.size() - 1;
   if (k <= n) {
      return y[k];
   }
   vector<ll> L(n + 1, 1);
   for (int x = 1; x <= n; ++x) {
      L[0] = L[0] * (k - x) % mod;
      L[0] = L[0] * inv(-x) % mod;
   }
   for (int x = 1; x <= n; ++x) {
      L[x] = L[x - 1] * inv(k - x) % mod * (k - (x - 1)) % mod;
      L[x] = L[x] * ((x - 1) - n + mod) % mod * inv(x) % mod;
   }
   ll yk = 0;
   for (int x = 0; x <= n; ++x) {
      yk = add(yk, L[x] * y[x] % mod);
   }
   return yk;
}
