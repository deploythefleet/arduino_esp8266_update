# Deploy the Fleet ESP8266 Library
This changelog is updated with each release and should contain the following sections if applicable:
  - **Added**: For any new features that have been added since the last version was released 
  - **Changed**: To note any changes to the software's existing functionality 
  - **Deprecated**: To note any features that were once stable but are no longer and have thus been removed 
  - **Fixed**: Any bugs or errors that have been fixed should be so noted 
  - **Removed**: This notes any features that have been deleted and removed from the software 
  - **Security**: This notes any security-related changes

----
# 2.0.0

Initial version to support v2 of Deploy the Fleet

### Changed
  - `getFirmwareUpdate` now accepts a product ID instead of a full update URL

----
# 1.0.7
### Changed
  - Improved memory efficiency
  - Use DTF Root X1 fingerprint instead of full cert chain
  - Only attempt to set NTP time once

----
# 1.0.6
### Added
  - Option to prevent automatic reboot of device after successful update
  - Additional fallback server with Deploy the Fleet operated TLS certificate
  - Library sends certificate bundle id

### Changed
  - NTP timeout reduced to 10 minutes from 16 hours

----
# 1.0.5
This is the first release tracked in the changelog.

### Fixed
  - Compile issues in new versions of Arduino IDE