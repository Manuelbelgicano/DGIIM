# diagmatrix Bash Prompt, based on the 'Sexy Bash Prompt'

if tput setaf 1 &> /dev/null; then
    if [[ $(tput colors) -ge 256 ]] 2>/dev/null; then
      COLORH=$(tput setaf 3)
      COLORU=$(tput setaf 4)
      COLORW=$(tput setaf 6)
      COLORGIT=$(tput setaf 2)
      COLORTEXT=$(tput setaf 1)
    else
      COLORH=$(tput setaf 11)
      COLORU=$(tput setaf 12)
      COLORW=$(tput setaf 14)
      COLORGIT=$(tput setaf 10)
      COLORTEXT=$(tput setaf 9)
    fi
    BOLD=$(tput bold)
    RESET=$(tput sgr0)
else
    COLORH="\033[1;31m"
    COLORU="\033[1;33m"
    COLORW="\033[1;32m"
    COLORGIT="\033[1;35m"
    COLORTEXT="\033[1;37m"
    BOLD=""
    RESET="\033[m"
fi

parse_git_dirty () {
  [[ $(git status 2> /dev/null | tail -n1 | cut -c 1-17) != "nothing to commit" ]] && echo "*"
}
parse_git_branch () {
  git branch --no-color 2> /dev/null | sed -e '/^[^*]/d' -e "s/* \(.*\)/\1$(parse_git_dirty)/"
}

function prompt_command() {
  PS1="\[${BOLD}${COLORTEXT}\[→ (\[${COLORH}\]\h\[${COLORTEXT}\[-\[${COLORU}\]\u\[${COLORTEXT}\[) in \[${COLORW}\[\w\[${COLORTEXT}\]\$([[ -n \$(git branch 2> /dev/null) ]] && echo \" on \")\[${COLORGIT}\]\$(parse_git_branch)\[${COLORTEXT}\]\n\[${BOLD}${COLORTEXT}\[→ \[${RESET}\]"
}

safe_append_prompt_command prompt_command