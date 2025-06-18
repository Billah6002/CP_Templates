
const int MOD = 1e9 + 7;
const int PRIMITIVE_ROOT = 3;

int mod_exp(int base, int exp, int mod) {
  int result = 1;
  while (exp > 0) {
    if (exp % 2 == 1) {
      result = (1LL * result * base) % mod;
    }
    base = (1LL * base * base) % mod;
    exp /= 2;
  }
  return result;
}

void ntt(vector<int> &a, bool invert) {
  int n = a.size();
  int log_n = log2(n);
  for (int i = 1, j = 0; i < n; i++) {
    int bit = n / 2;
    while (j >= bit) {
      j -= bit;
      bit /= 2;
    }
    j += bit;
    if (i < j) swap(a[i], a[j]);
  }
  for (int len = 2; len <= n; len *= 2) {
    int wlen = mod_exp(PRIMITIVE_ROOT, (MOD - 1) / len, MOD);
    if (invert) wlen = mod_exp(wlen, MOD - 2, MOD);
    for (int i = 0; i < n; i += len) {
      int w = 1;
      for (int j = 0; j < len / 2; j++) {
        int u = a[i + j];
        int v = (1LL * a[i + j + len / 2] * w) % MOD;
        a[i + j] = (u + v) % MOD;
        a[i + j + len / 2] = (u - v + MOD) % MOD;
        w = (1LL * w * wlen) % MOD;
      }
    }
  }
  if (invert) {
    int n_inv = mod_exp(n, MOD - 2, MOD);
    for (int &x : a) {
      x = (1LL * x * n_inv) % MOD;
    }
  }
}

vector<int> multiply(vector<int> const &a, vector<int> const &b) {
  int n = 1;
  while (n < a.size() + b.size()) n *= 2;
  vector<int> fa(a.begin(), a.end()), fb(b.begin(), b.end());
  fa.resize(n);
  fb.resize(n);
  ntt(fa, false);
  ntt(fb, false);
  for (int i = 0; i < n; i++) {
    fa[i] = (1LL * fa[i] * fb[i]) % MOD;
  }
  ntt(fa, true);
  while (!fa.empty() && fa.back() == 0) fa.pop_back();
  return fa;
}
