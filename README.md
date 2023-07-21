# vd_agent

## Introduction

This repository contains the source code for the `vd_agent` application. This application is designed to change your current resolution to arbitrary or custom resolution, it is designed to run on the Windows platform and is specifically tailored to work with the SPICE (QXL) display adapter when SPICE guest tools are installed.

## Requirements

- Windows Operating System
- SPICE (QXL) display adapter
- SPICE guest tools installed: [Download](https://www.spice-space.org/download/windows/spice-guest-tools/spice-guest-tools-latest.exe)

## Download and Run

- Download the latest [vdagent.exe](https://github.com/anandphulwani/vd_agent/releases/latest/download/vdagent.exe) executable from the release section, and you are ready to use.

## Usage

To use VD Agent, you can run the following commands:

- To set the resolution width and height: `vdagent --width <value>  --height <value>`
- To set the log level to INFO, append to command: `--info`
- To set the log level to TRACE, append to command: `--trace`

For example, to set the resolution to 1920x1080 and the log level to INFO, you would run: `vdagent --width 1920 --height 1080 --info`


## Known Issues

When using Proxmox and the SPICE display adapter is set, the SPICE viewer works perfectly. However, if noVNC is used, the mouse pointer may vary and misbehave. To resolve this issue, you will need to install the
- [VMware mouse driver](https://github.com/anandphulwani/vd_agent/releases/latest/download/VMware-tools-windows-9.4.6_MouseDrivers.rar) (for Proxmox users experiencing issues with noVNC)

## Modify and/or Compilation

To compile the `vd_agent` application, take care of the following point:
- The compilation can build only on a **Fedora operating system** (FYI: by default, fedora doesn't show icons on desktop.) with the steps laid down below.
- Make sure line endings do not change while cloning/commiting/pushing.
- Make sure a single tag exists, as it is required to `make` the repository.
- Make sure the `autogen.sh` has executable rights (-rwxr-xr-x.), and the rest of directories and files have proper rights and ownership.


Then you will need to clone the repository and run commands in the following way:

```bash
cd ~/Desktop
sudo dnf install git libtool make ImageMagick autoconf-archive wine-core.x86_64 wine-core.i686 mingw32-libpng-static mingw32-zlib-static mingw32-gcc-c++ mingw32-winpthreads-static mingw64-libpng-static mingw64-zlib-static mingw64-gcc-c++ mingw64-winpthreads-static
mkdir vd_agent && cd vd_agent
git config --get core.autocrlf
git config --global core.autocrlf false # To avoid changing line endings while cloning/commiting/pushing.
git clone https://github.com/anandphulwani/vd_agent.git .
git tag -l # Make sure a single tag exists, as it is required to `make` the repository, if no tag is found run the below command by removing the #.
# git tag -a v201.0.0 && git tag -l
ls -al autogen.sh # Make sure the `autogen.sh` has executable rights (-rwxr-xr-x.).
ls -al | grep "^d" # Make sure the directory rights are 755 (-rwxr-xr-x.)
ls -al | grep -v "^d" # Make sure the files rights are 644 (-rw-r--r--.) or 755 (-rwxr-xr-x.)
ls -al # Make sure the owner and group is your current user (user user, in my case)
```
- Make the code modifications over here, if any. Then run the following commands:
```bash
git diff -U0 # Check differences made with line numbers
git add *
git commit -m "<COMMIT MESSAGE HERE>"
git tag -a v201.0.0
git tag -l
```

- Push the code modifications to remote, if any modifications are done:
```bash
git remote -v
git remote rm origin
git remote add origin <YOUR REPO URL HERE>
git branch -M master
git push -u origin master
git push -u origin --tags
```

- To compile, run the following commands:
```bash
./autogen.sh
make distclean # This will return a failure the first time
mingw64-configure
mingw64-make
mingw64-make check # This will launch a WINE installer the first time, please click on Install/Agree if you are prompted.
```

## Source and Reference URLs

- [vd_agent Win32](https://gitlab.freedesktop.org/spice/win32/vd_agent) The primary source code for `vd_agent` from which this repository is copied at this [commit](https://gitlab.freedesktop.org/spice/win32/vd_agent/-/commit/50175107091d5640cb0bb251807a9fcbae85f0f2).
- [SPICE Downloads Page](https://www.spice-space.org/download.html)
- [spice-protocol](https://gitlab.freedesktop.org/spice/spice-protocol) `Spice Protocol` is used as a sub module/ sub directory in the project directory.
- [spice-common](https://gitlab.freedesktop.org/spice/spice-common) `Spice Common` is used as a sub module/ sub directory in the project directory.
- [SPICE Group Repository](https://gitlab.freedesktop.org/spice)
- [SPICE WIN32 Group Repository](https://gitlab.freedesktop.org/spice/win32)
- [win32/qxl driver](https://gitlab.freedesktop.org/spice/win32/qxl) and [win32/qxl-wddm-dod driver](https://gitlab.freedesktop.org/spice/win32/qxl-wddm-dod).
- [vd_agent Linux](https://gitlab.freedesktop.org/spice/linux/vd_agent)

## Other Reference URLs
- Change resolution lead to a freeze of the vd-agent: [https://gitlab.freedesktop.org/spice/win32/vd_agent/-/issues/20](https://gitlab.freedesktop.org/spice/win32/vd_agent/-/issues/20)
- Resize to arbitrary resolution Use QXL_ESCAPE_SET_CUSTOM_DISPLAY to update custom mode, and switch to it: [https://gitlab.freedesktop.org/spice/win32/vd_agent/-/commit/3d45018086688697bc5d3686b9fd47a079155094?view=inline](https://gitlab.freedesktop.org/spice/win32/vd_agent/-/commit/3d45018086688697bc5d3686b9fd47a079155094?view=inline)
- [http://tools.taubenkorb.at/change-screen-resolution/](http://tools.taubenkorb.at/change-screen-resolution/)
- [https://packages.vmware.com/tools/esx/5.5p02/windows/](https://packages.vmware.com/tools/esx/5.5p02/windows/) VMware-tools-9.4.6-1770165-x86_64

Please note that these resources are external to the `vd_agent` project and may contain information that is beyond the scope of `vd_agent` itself. They are provided for reference purposes only.

## Alternatives (For non arbitrary/custom resolution, non QXL drivers)
01. ToastyX cru-1.5.2: [Homepage](https://www.monitortests.com/forum/Thread-Custom-Resolution-Utility-CRU), [Download](https://www.monitortests.com/download/cru/cru-1.5.2.zip), [How to use](https://www.youtube.com/watch?v=dpcte_5u1tg)
01. [change-screen-resolution](http://tools.taubenkorb.at/change-screen-resolution/)
02. [QRes](http://qres.sourceforge.net/): Works on my Windows 7.
03. [Display Changer II](http://12noon.com/?page_id=641): For changing the resolution, starting a program and restoring the resolution.
04. [NirCmd](http://www.nirsoft.net/utils/nircmd.html): Tool for some useful tasks. Call eg nircmd.exe setdisplay 1024 768 24
05. [MultiRes](http://www.entechtaiwan.com/util/multires.shtm): Command line tool to change settings for multiple monitors.
06. [Res](http://www.memecode.com/res.php): Command line tool to change settings for specific monitors.

## Conclusion

The `vd_agent` application is a powerful tool for managing the SPICE (QXL) display adapter on Windows systems. Please ensure that you have the necessary system requirements and follow the provided instructions. If you encounter any issues, please report them on the repository.

## Contributing
Contributions to vd_agent are welcome!

## License

vd_agent is licensed under the GPL-3.0 license.
