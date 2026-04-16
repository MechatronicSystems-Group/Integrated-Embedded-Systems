# Repository Guidelines

## Project Structure & Module Organization

This repository hosts the MEC4126F course website and supporting embedded template material. Course pages live in `analogue-electronics/`, `microcontroller-programming/`, `practicals/`, and `appendix/`. Shared site components live in `_layouts/`, `_includes/`, `_sass/`, and `assets/`. Keep teaching assets close to the page that uses them, for example `practicals/practical_5/Resources/` or `microcontroller-programming/images/`. The STM32 reference project is separate in `STM32-Programming-Template/`, with code under `Core/Src` and headers under `Core/Inc`.

## Build, Test, and Development Commands

Use Bundler for website work and `make` for the STM32 example.

- `bundle install`: install the Jekyll dependencies from `Gemfile`.
- `bundle exec jekyll serve`: preview the site locally while editing notes, practicals, or navigation.
- `bundle exec jekyll build`: required pre-PR check; this matches CI and GitHub Pages.
- `make -C STM32-Programming-Template`: build the embedded template into `STM32-Programming-Template/build/`.
- `make -C STM32-Programming-Template clean`: remove generated firmware artifacts.

## Coding Style & Naming Conventions

Markdown pages should include YAML front matter and use descriptive filenames such as `chapter-10-adc.md` or `prac-6-PWM.md`. Preserve the current course naming scheme and navigation ordering. When adding a new chapter or practical, keep related images, PDFs, and handouts in a local `images/` or `Resources/` folder rather than the repo root. For STM32 code, follow the existing C style: 4-space indentation, clear comments, and `snake_case` for project-defined functions and variables.

## Course Maintenance Workflow

For content changes, verify the affected page in the local Jekyll site and confirm links, figures, Mermaid blocks, and PDFs render correctly. For practical releases, check the practical index, due-date wording, and any linked marking guides or resources. For STM32 template edits, require a clean `make -C STM32-Programming-Template` build before merging.

## Commit & Pull Request Guidelines

Recent commits use short, imperative summaries such as `Update ch9 and prac6` and `add git slides`. Keep the same style: brief, specific, and action-oriented. Pull requests should state which course section was updated, whether the change affects students directly, and how it was validated. Include screenshots for visible layout changes and mention firmware build results when touching `STM32-Programming-Template/`.
