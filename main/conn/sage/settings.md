# Data Structure
Namespace: `d::conn::sage::settings::files`
```cpp
struct files {
    ofstream scriptf, plotf, dataf;
    std::string script, plot, data;
    const bool rmData, rmScript, rmPlot;
}
```

# Constructor
```cpp
files()
files(std::string pl)
files(std::string pl, std::string da)
files(std::string pl, std::string da, std::string sc)
```
