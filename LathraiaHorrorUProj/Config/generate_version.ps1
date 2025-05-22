param (
    [string]$configFile,
    [string]$section,
    [string]$variable,
    [string]$newValue
)

$lines = Get-Content $configFile
$insideSection = $false
$variableFound = $false
$output = @()

foreach ($line in $lines) {
    if ($line -match "^\[.*\]$") {
        $insideSection = ($line -eq $section)
    }
    if ($insideSection -and $line -match ("^" + [regex]::Escape($variable) + "=")) {
        $line = "$variable=$newValue"
        $variableFound = $true
    }
    $output += $line
}

if (-not $variableFound) {
    $output += $variable + "=" + $newValue
}

$output | Set-Content $configFile