# sumo_game

[![ci](https://github.com/valerioformato/sumo_game/actions/workflows/ci.yml/badge.svg)](https://github.com/valerioformato/sumo_game/actions/workflows/ci.yml)
[![codecov](https://codecov.io/gh/valerioformato/sumo_game/branch/main/graph/badge.svg)](https://codecov.io/gh/valerioformato/sumo_game)
[![CodeQL](https://github.com/valerioformato/sumo_game/actions/workflows/codeql-analysis.yml/badge.svg)](https://github.com/valerioformato/sumo_game/actions/workflows/codeql-analysis.yml)

LGTM Has to be set up manually after template is created:

[![Language grade: C++](https://img.shields.io/lgtm/grade/cpp/github/valerioformato/sumo_game)](https://lgtm.com/projects/g/valerioformato/sumo_game/context:cpp)

## About sumo_game



## More Details
### Disabled warnings
- *cppcheck*
    - `unusedPrivateFunction`: This check triggers false positives too often, especially when a private class member is used in a lambda function and/or as an argument for `std::thread` or `std::jthread`.
- *clang-tidy*
    - ![just kidding](https://i.imgflip.com/6c4c38.jpg)
