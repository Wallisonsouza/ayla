#pragma once

class CompilationUnit;

class Stage {
public:
  virtual ~Stage() = default;

  virtual void run(CompilationUnit &unit) = 0;
};