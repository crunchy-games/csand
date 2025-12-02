require("assets.api.modding") -- must use `assets.api.modding`

-- the 'init' function. ALL mods need this function. It edits
-- the API's config to better handle the mod.
function init()
  if (api == nil) then
    print("COULD NOT LOAD API")
    os.exit(1) -- exit with an error if the API could not be found
  end

  -- sets the config for the API. All settings set here are required
  -- by all mods.
  api_settings.mod_configs["example_mod"] = {
    name="Example Mod",
    version="1.0.0",
    author="Mod Author",
    description="An example mod that demonstrates the modding API.",
    meta={
      required_permissions="limited", -- options are "limited" and "full", "full" must be selected if it needs file access
      recommended_permissions="limited", -- same options as above. this does _not_ reflect the required permissions, only recommended ones from the devs
      data_path="" -- can be left an empty string if no file-related functions are called. Otherwise, have it to be set as a local folder (i.e, "mod_data/")
    }
  }
end

