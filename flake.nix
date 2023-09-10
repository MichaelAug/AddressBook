{
  description = "My C++ Project Development Environment";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };
  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem
      (system:
        let
          pkgs = import nixpkgs {
            inherit system;
          };
        in
        with pkgs;
        {

          devShells.default = mkShell {

            buildInputs = with nixpkgs; [
              cmake
              clang
              clang-tools
              ninja
              gdb
              gtest

              jdk17 # SonarLint language server dependency
            ];
          };
        }
      );
}
