import path from 'path';
import { command } from '@josephuspaye/powershell';

const exe = path.join(__dirname, '..', 'bin', 'ShowProperties.exe');

/**
 * Show the Explorer properties dialog for the file or folder at the given path.
 * Returns the exit code of the launcher process (not the launched dialog process).
 */
export async function showProperties(targetPath: string) {
  if (!targetPath || targetPath.trim().length === 0) {
    throw new Error('target path is required to show properties');
  }

  const output = await command(
    `Start-Process -WindowStyle Hidden -FilePath "${exe}" -ArgumentList "${targetPath}"`
  );

  return output.exitCode;
}
