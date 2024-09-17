import re
from os import path

def constant_case(technique: str) -> str:
    return "_".join(technique.upper().split(" "))

def pascal_case(technique: str) -> str:
    return "".join(technique.title().split(" "))

def snake_case(technique: str) -> str:
    return "_".join(technique.lower().split(" "))

def source_file(technique: str) -> str:
    return snake_case(technique) + ".cxx"

def header_file(technique: str) -> str:
    return snake_case(technique) + ".h"

def read_format_file(format_name: str) -> str:
    file_path = path.join(path.abspath(path.dirname(__file__)), "resources", format_name)
    with open(file_path, "r") as file:
        return file.read()

def write_formatted_file(path: str, format_name: str, technique: str) -> bool:
    file_content = read_format_file(format_name)
    with open(path, "w+") as file:
        file.write(file_content.format(class_name=pascal_case(technique), header_file=header_file(technique), enum_name=constant_case(technique)))
    return True

def add_to_CMakeLists(technique: str, dir: str) -> bool:
    cmake_filename = path.join(dir, "CMakeLists.txt")
    cmake_content = ""
    with open(cmake_filename, "r") as cmake_file:
        cmake_content = cmake_file.read()
    source_files_set_regex = r"(?s)set\(source_files(.*?)\)"
    replacement = f"set(source_files\\1  {source_file(technique)}\n)"
    cmake_content = re.sub(source_files_set_regex, replacement, cmake_content)
    with open(cmake_filename, "w") as cmake_file:
        cmake_file.write(cmake_content)
    return True

def add_to_enum(technique: str, dir: str) -> bool:
    enum_filename = path.join(dir, "technique_enum.hpp")
    enum_content = ""
    with open(enum_filename, "r") as enum_file:
        enum_content = enum_file.read()
    enum_regex = r"(?s)enum class TechniqueEnum \{(.*?)\n\};"
    replacement = f"enum class TechniqueEnum {{\\1,\n  {constant_case(technique)}\n}};"
    enum_content = re.sub(enum_regex, replacement, enum_content)
    with open(enum_filename, "w") as enum_file:
        enum_file.write(enum_content)
    return True

def add_technique_to_logic(technique: str, source_dir: str) -> bool:
    logic_dir = path.join(source_dir, "generator", "logic")
    if not add_to_CMakeLists(technique, logic_dir):
        return False
    if not add_to_enum(technique, logic_dir):
        return False
    if not write_formatted_file(path.join(logic_dir, header_file(technique)), "header.txt", technique):
        return False
    if not write_formatted_file(path.join(logic_dir, source_file(technique)), "source.txt", technique):
        return False
    return True

def add_technique_to_test(technique: str, source_dir: str) -> bool:
    test_dir = path.join(source_dir, "test")
    if not add_to_CMakeLists(technique, test_dir):
        return False
    if not write_formatted_file(path.join(test_dir, source_file(technique)), "test.txt", technique):
        return False
    return True

def main():
    technique = input("Enter technique: ").lower()
    source_dir = path.join(path.abspath(path.dirname(__file__)), "..", "src")
    if not add_technique_to_logic(technique, source_dir):
        return
    if not add_technique_to_test(technique, source_dir):
        return

if __name__ == "__main__":
    main()
